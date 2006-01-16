/*
   ktigcc - TIGCC IDE for KDE
   
   tpr handling routines adapted from tprbuilder
   Copyright (C) 2002 Romain Liévin
   Copyright (C) 2002-2006 Kevin Kofler
   Copyright (C) 2006 Joey Adams

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <kapplication.h>
#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <qtextcodec.h>
#include "tpr.h"

#define find_param(s_,t_) find_param_ex((s_),(t_),sizeof(t_)-1)

char *find_param_ex(char *s, const char *t, size_t l)
{
  if (!strncmp(s,t,l))
    return s+l;
  else
    return NULL;
}

char *find_numbered_param(char *s, const char*t, int *i)
{
    char *p;
    int endpos = 0;
    int ret = 0;
    char arglist[256];
    
    strcpy(arglist, t);
    strcat(arglist, "%n");
    
    ret = sscanf(s, arglist, i, &endpos);
    if(ret < 1 || !endpos) return NULL;
    
    p = s + endpos;
    return p;
}

// converts Windows paths to Unix paths if necessary.
QString convert_path_separators(const char *file)
{
    QString s=file;
    int o;
  
#ifndef __WIN32__
     while ((o=s.find('\\',0,TRUE))>=0)
         s[o]='/';
#endif
    
    return s;
}

char* strip(char *str)
{
    int len = strlen(str);

    if(len > 0)
        if( (str[len-1] == '\r') || (str[len-1] == '\n') )
            str[len-1] = '\0';
    
    if(len > 1)
        if( (str[len-2] == '\r') || (str[len-2] == '\n') )
            str[len-2] = '\0';

    return str;
}

/* 
   Read a line from file and do a clean-up 
*/
int read_line(FILE *f, char *buffer, int *l)
{
    strcpy(buffer, "");
    if(feof(f)) return EOF;
    fgets(buffer, 256, f);
    strip(buffer);
    (*l)++;
    while( (buffer[0] == '\r') || (buffer[0] == '\n') || (buffer[0] == '\0') )
    {
        if(feof(f)) return EOF;
        fgets(buffer, 256, f);
        strip(buffer);
        (*l)++;
    }
    
    return 0;
}

//some items from the TSR might still be ignored or not shown here.
//if you need one of them, add an entry to one of the
//definition "tables".
int parse_file(FILE *f,TPRDataStruct *dest)
{
  char buffer[256];
  int l = 0;
  SectionType stype = SECTION_NONE;
  
  // Some defaults are different when opening an existing project.
  dest->settings.cc_switches="";
  dest->settings.as_switches="";
  dest->settings.a68k_switches="";
  dest->libopts.use_ti89=0;
  dest->libopts.use_ti92p=0;
  dest->libopts.use_v200=0;
  dest->libopts.use_minams=0;
  dest->libopts.save_screen=0;

  while(!feof(f)) 
    {
        char *p;
          
        // Get a line from file
        if(read_line(f, buffer, &l) == EOF) break;

        // Search for sections
        if( !strcmp(buffer, "[Settings]") )
        {
            stype = SECTION_SETTINGS;
            continue;
        }
        
        if( !strcmp(buffer, "[Library Options]") )
        {
            stype = SECTION_LIBOPTS;
            continue;
        }
        
        if( !strcmp(buffer, "[File Editing]") )
        {
            stype = SECTION_FILEEDIT;
            continue;
        }
        
        if( !strcmp(buffer, "[Included Files]") )
        {
            stype = SECTION_FILES;
            continue;
        }
        
        // Keywords in the [Settings] section
        if(stype == SECTION_SETTINGS) {

#define boolean_param(token,setting) \
            if ( (p=find_param(buffer, token)) ) \
            { \
                if(!strcmp(p, "0")) dest->settings.setting = FALSE; \
                else if(!strcmp(p, "1")) dest->settings.setting = TRUE; \
                else return l; \
                continue; \
            } else

#define string_vparam(token,var) \
            if ( (p=find_param(buffer, token)) ) \
            { \
                if (*p) dest->var = p; \
                continue; \
            } else

#define string_param(token,setting) string_vparam(token,settings.setting)

#define ignore_param(token) \
            if( (p=find_param(buffer, token)) ) \
            { \
                continue; \
            } else

            boolean_param("Archive=",archive)
            boolean_param("Pack=",pack)
            string_param("Packed Variable=",pack_name)
            string_vparam("Project Name=",prj_name)
            string_param("GCC Switches=",cc_switches)
            string_param("Assembler Switches=",a68k_switches)
            ignore_param("Linker Switches=") // Obsolete. Ignore.
            ignore_param("GNU Linker Switches=") // Obsolete. Ignore.
            string_param("GNU Assembler Switches=",as_switches)
            ignore_param("BSR Patch=") // Obsolete. Ignore.
            boolean_param("Debug Info=",debug_info)
            boolean_param("Standard Library=",std_lib)
            string_param("Command Line=",cmd_line)
            string_param("Post-Build Process=",post_build)
            boolean_param("Use Data Variable=",use_data_var)
            string_param("Data Variable=",data_var)
            boolean_param("Copy Data Variable=",copy_data_var)
            boolean_param("Copy Data Variable if Archived=",copy_data_var_arc)
            boolean_param("Optimize NOPs=",optimize_nops)
            boolean_param("Optimize Returns=",optimize_returns)
            boolean_param("Optimize Branches=",optimize_branches)
            boolean_param("Optimize Moves=",optimize_moves)
            boolean_param("Optimize Tests=",optimize_tests)
            boolean_param("Optimize Calculations=",optimize_calcs)
            boolean_param("Remove Unused Sections=",remove_unused)
            boolean_param("Binary Output=",outputbin)
            boolean_param("Fargo=",fargo)
            boolean_param("Flash OS=",flash_os)
            boolean_param("Cut Unused Ranges=",cut_ranges)
            boolean_param("Reorder Sections=",reorder_sections)
            boolean_param("Merge Constants=",merge_constants)
            boolean_param("Initialize BSS=",initialize_bss)
            return l;

#undef boolean_param
#undef string_vparam
#undef string_param
#undef ignore_param
        }
        
        // Keywords in the [Library Options] section
        if(stype == SECTION_LIBOPTS) {
#define boolean_param(token,setting) \
            if ( (p=find_param(buffer, token)) ) \
            { \
                if(!strcmp(p, "0")) dest->libopts.setting = FALSE; \
                else if(!strcmp(p, "1")) dest->libopts.setting = TRUE; \
                else return l; \
                continue; \
            } else

#define reloc_param(token,setting) \
            if ( (p=find_param(buffer, token)) ) \
            { \
                if (!strcmp(p,"None") || !strcmp(p,"AMS") \
                    || !strcmp(p,"Direct")) \
                    dest->libopts.setting = RT_NONE; \
                else if (!strcmp(p, "Precomputed")) \
                    dest->libopts.setting = RT_PRECOMP; \
                else if (!strcmp(p, "Kernel")) \
                    dest->libopts.setting = RT_KERNEL; \
                else if (!strcmp(p, "Compressed")) \
                    dest->libopts.setting = RT_COMPRESSED; \
                else if (!strcmp(p, "F-Line")) \
                    dest->libopts.setting = RT_FLINE; \
                else if (strcmp(p, "Unknown")) \
                    return l; \
                continue; \
            } else

            boolean_param("Use TI-89=",use_ti89)
            boolean_param("Use TI-92 Plus=",use_ti92p)
            boolean_param("Use V200=",use_v200)
            boolean_param("Optimize Calc Consts=",opt_calc_consts)
            boolean_param("Use Kernel=",use_kernel)
            boolean_param("Use PreOS=",use_preos)
            boolean_param("Minimum AMS Version Defined=",use_minams)
            if ( (p=find_param(buffer, "Minimum AMS Version=")) )
            {
                int major, minor;
                if ((strlen(p)==4) && (sscanf(p,"%1d.%2d",&major,&minor)==2))
                    dest->libopts.minams = major * 100 + minor;
                else
                    return l;
                continue;
            } else
            boolean_param("Unofficial OS Support=",unofficial_os)
            reloc_param("Reloc Format=",reloc_format)
            reloc_param("ROM Call Format=",rom_call_format)
            reloc_param("BSS Ref Format=",bss_ref_format)
            reloc_param("Data Ref Format=",data_ref_format)
            boolean_param("Use F-Line Jumps=",use_fline_jumps)
            boolean_param("Use 4-Byte F-Line Jumps=",use_4b_fline_jumps)
            boolean_param("Use Internal F-Line Emulator=",use_internal_fline_emu)
            boolean_param("Use Return Value=",use_return_value)
            boolean_param("Enable Error Return=",enable_error_return)
            boolean_param("Save Screen=",save_screen)
            boolean_param("Optimize ROM Calls=",opt_rom_calls)
            return l;

#undef boolean_param
#undef reloc_param
        }

        // Ignore [File Editing] section, it is used only for editing.

        // Keywords in the [Included Files] section
        if(stype == SECTION_FILES)
        {
            int v;

            if( (p=find_numbered_param(buffer, "C File %i=", &v)) )
            {
                QString s = convert_path_separators(p);
                dest->c_files.path << s;
                dest->c_files.folder << QString::null;

                continue;
            }
            else if( (p=find_numbered_param(buffer, "C File %i Folder=", &v)) )
            {
                
                continue;
            }

            else if( (p=find_numbered_param(buffer, "GNU Assembler File %i=", &v)) )
            {
                QString s = convert_path_separators(p);
                dest->s_files.path << s;
                dest->s_files.folder << QString::null;
              
                continue;
            }
            else if( (p=find_numbered_param(buffer, "GNU Assembler File %i Folder=", &v)) )
            { // ignore folder specification for now
                continue;
            }

            else if( (p=find_numbered_param(buffer, "Header File %i=", &v)) )
            {
                QString s = convert_path_separators(p);
                dest->h_files.path << s;
                dest->h_files.folder << QString::null;
                
                continue;
            }
            else if( (p=find_numbered_param(buffer, "Header File %i Folder=", &v)) )
            { // ignore folder specification for now
                continue;
            }

            else if( (p=find_numbered_param(buffer, "Assembler File %i=", &v)) )
            {
                QString s = convert_path_separators(p);
                dest->asm_files.path << s;
                dest->asm_files.folder << QString::null;
              
                continue;
            }
            else if( (p=find_numbered_param(buffer, "Assembler File %i Folder=", &v)) )
            { // ignore folder specification for now
                continue;
            }

            else if( (p=find_numbered_param(buffer, "Object File %i=", &v)) )
            {
                QString s = convert_path_separators(p);
                dest->o_files.path << s;
                dest->o_files.folder << QString::null;
              
                continue;
            }
            else if( (p=find_numbered_param(buffer, "Object File %i Folder=", &v)) )
            { // ignore folder specification for now
                continue;
            }

            else if( (p=find_numbered_param(buffer, "Archive File %i=", &v)) )
            {
                QString s = convert_path_separators(p);
                dest->a_files.path << s;
                dest->a_files.folder << QString::null;
              
                continue;
            }
            else if( (p=find_numbered_param(buffer, "Archive File %i Folder=", &v)) )
            { // ignore folder specification for now
                continue;
            }

            else if( (p=find_numbered_param(buffer, "Text File %i=", &v)) )
            {
                QString s = convert_path_separators(p);
                dest->txt_files.path << s;
                dest->txt_files.folder << QString::null;
              
                continue;
            }
            else if( (p=find_numbered_param(buffer, "Text File %i Folder=", &v)) )
            { // ignore folder specification for now
                continue;
            }

            else if( (p=find_numbered_param(buffer, "Quill File %i=", &v)) )
            {
                QString s = convert_path_separators(p);
                dest->quill_files.path << s;
                dest->quill_files.folder << QString::null;

                continue;
            }
            else if( (p=find_numbered_param(buffer, "Quill File %i Folder=", &v)) )
            { // ignore folder specification for now
                continue;
            }

            else if( (p=find_numbered_param(buffer, "Other File %i=", &v)) )
            {
                QString s = convert_path_separators(p);
                dest->oth_files.path << s;
                dest->oth_files.folder << QString::null;
                
                continue;
            }
            else if( (p=find_numbered_param(buffer, "Other File %i Folder=", &v)) )
            { // ignore folder specification for now
                continue;
            }

            else return l;
        }

    }

    return 0;
}

//returns 0 on success
int loadTPR(QString &fileName,TPRDataStruct *dest)
{
  FILE *f;
  int ret;
  f = fopen(fileName, "r");
  if(f == NULL) {
      return -1;
  }
  ret=parse_file(f,dest);
  fclose(f);
  return ret;
}

QString loadFileText(const char *fileName)
{
  FILE *f;
  f=fopen(fileName,"rb");
  if (!f)
    return QString::null;
  fseek(f,0,SEEK_END);
  size_t flen=ftell(f);
  fseek(f,0,SEEK_SET);
  char buffer[flen+1];
  memset(buffer,0,flen+1);
  fread(buffer,1,flen,f);
  return QString(buffer);
}
