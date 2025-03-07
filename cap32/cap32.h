/* Caprice32 - Amstrad CPC Emulator
   (c) Copyright 1997-2005 Ulrich Doewich

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef CAP32_H
#define CAP32_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <retro_endianness.h>

//RETRO HACK
//TODO ENDIANNESS
//#define DEBUG 1
//#define DEBUG_CRTC
//#define DEBUG_CART
//#define DEBUG_ASIC
//#define DEBUG_FDC
//#define DEBUG_GA
//#define DEBUG_NO_VIDEO
//#define DEBUG_TAPE
//#define DEBUG_Z80

#ifndef TARGET_GNW
#ifndef _MAX_PATH
 #ifdef _POSIX_PATH_MAX
 #define _MAX_PATH _POSIX_PATH_MAX
 #else
 #define _MAX_PATH 256
 #endif
#endif
#else
#define _MAX_PATH 2
#endif

#define CPC_BASE_FREQUENCY_MHZ 4.0
#define FRAME_PERIOD_MS        20.0
#define CYCLE_COUNT_INIT (CPC_BASE_FREQUENCY_MHZ*FRAME_PERIOD_MS*1000)


// max emulated RAM is 64 + 512
// https://www.grimware.org/doku.php/documentations/devices/gatearraydo=export_xhtml#mmr
#ifndef TARGET_GNW
#define CPC_MAX_RAM 576
#else
#define CPC_MAX_RAM 128
#endif

#define CPC_SCR_WIDTH 1024 // max width
#define CPC_SCR_HEIGHT 312 // max height
#define CPC_VISIBLE_SCR_WIDTH 384 // visible width: 4+40+4 * 8
#define CPC_VISIBLE_SCR_HEIGHT 270

#define CPC_MONITOR_COLOR 0
#define CPC_MONITOR_GREEN 1
#define CPC_MONITOR_WHITE 2

#define CPC_MODEL_464 0
#define CPC_MODEL_664 1
#define CPC_MODEL_6128 2
#ifndef TARGET_GNW
#define CPC_MODEL_PLUS 3
#define CPC_MODEL_MAX 3
#else
#define CPC_MODEL_MAX 2
#endif

#define ICN_DISK_WIDTH 14
#define ICN_DISK_HEIGHT 16
#define ICN_TAPE_WIDTH 18
#define ICN_TAPE_HEIGHT 13

#define VOC_THRESHOLD 128

// CRTC flags
#define VS_flag      1
#define HS_flag      2
#define HDT_flag     4
#define VDT_flag     8
#define HT_flag      16
#define VT_flag      32
#define MR_flag      64
#define VTadj_flag   128
#define VSf_flag     256

// FDC constants
#define DSK_BPTMAX      8192
#define DSK_TRACKMAX    102   // max amount that fits in a DSK header
#define DSK_SIDEMAX     2
#define DSK_SECTORMAX   29    // max amount that fits in a track header

#define FDC_TO_CPU      0
#define CPU_TO_FDC      1

#define CMD_PHASE       0
#define EXEC_PHASE      1
#define RESULT_PHASE    2

#define SKIP_flag       1     // skip sectors with DDAM/DAM
#define SEEKDRVA_flag   2     // seek operation has finished for drive A
#define SEEKDRVB_flag   4     // seek operation has finished for drive B
#define RNDDE_flag      8     // simulate random DE sectors
#define OVERRUN_flag    16    // data transfer timed out
#define SCAN_flag       32    // one of the three scan commands is active
#define SCANFAILED_flag 64    // memory and sector data does not match
#define STATUSDRVA_flag 128   // status change of drive A
#define STATUSDRVB_flag 256   // status change of drive B

// Multiface 2 flags
#define MF2_ACTIVE      1
#define MF2_RUNNING     2
#define MF2_INVISIBLE   4

// SNA INFO: https://www.cpcwiki.eu/index.php/Format:SNA_snapshot_file_format
#define SNA_ID          8
#define SNA_ID_UNUSED   8

typedef struct {
   char id[SNA_ID];
   char unused1[SNA_ID_UNUSED];
   unsigned char version;
   unsigned char AF[2];
   unsigned char BC[2];
   unsigned char DE[2];
   unsigned char HL[2];
   unsigned char R;
   unsigned char I;
   unsigned char IFF0;
   unsigned char IFF1;
   unsigned char IX[2];
   unsigned char IY[2];
   unsigned char SP[2];
   unsigned char PC[2];
   unsigned char IM;
   unsigned char AFx[2];
   unsigned char BCx[2];
   unsigned char DEx[2];
   unsigned char HLx[2];
   unsigned char ga_pen;
   unsigned char ga_ink_values[17];
   unsigned char ga_ROM_config;
   unsigned char ga_RAM_config;
   unsigned char crtc_reg_select;
   unsigned char crtc_registers[18];
   unsigned char upper_ROM;
   unsigned char ppi_A;
   unsigned char ppi_B;
   unsigned char ppi_C;
   unsigned char ppi_control;
   unsigned char psg_reg_select;
   unsigned char psg_registers[16];
   unsigned char ram_size[2];
// version 2 info follows
   unsigned char cpc_model;
   unsigned char last_interrupt;
   unsigned char scr_modes[6];
// version 3 info follows
   unsigned char drvA_DOSfilename[13];
   unsigned char drvB_DOSfilename[13];
   unsigned char cart_DOSfilename[13];
   unsigned char fdc_motor;
   unsigned char drvA_current_track;
   unsigned char drvB_current_track;
   unsigned char drvC_current_track;
   unsigned char drvD_current_track;
   unsigned char printer_data;
   unsigned char psg_env_step;
   unsigned char psg_env_direction;
   unsigned char crtc_type;
   unsigned char crtc_addr[2];
   unsigned char crtc_scanline[2];
   unsigned char crtc_char_count[2];
   unsigned char crtc_line_count;
   unsigned char crtc_raster_count;
   unsigned char crtc_vt_adjust_count;
   unsigned char crtc_hsw_count;
   unsigned char crtc_vsw_count;
   unsigned char crtc_flags[2];
   unsigned char ga_int_delay;
   unsigned char ga_sl_count;
   unsigned char z80_int_pending;
   unsigned char unused2[75];
} t_SNA_header;

typedef struct {
   char id[34];
   char unused1[14];
   unsigned char tracks;
   unsigned char sides;
   unsigned char unused2[2];
   unsigned char track_size[DSK_TRACKMAX*DSK_SIDEMAX];
} t_DSK_header;

typedef struct {
   char id[12];
   char unused1[4];
   unsigned char track;
   unsigned char side;
   unsigned char unused2[2];
   unsigned char bps;
   unsigned char sectors;
   unsigned char gap3;
   unsigned char filler;
   unsigned char sector[DSK_SECTORMAX][8];
} t_track_header;



typedef struct {
   unsigned int model;
   unsigned int jumpers;
   unsigned int ram_size;
   unsigned int speed;
   unsigned int paused;
   unsigned int keyboard_line;
   unsigned int tape_motor;
   unsigned int tape_play_button;
   unsigned int printer;
   unsigned int printer_port;
#ifndef TARGET_GNW
   unsigned int mf2;
#endif
   unsigned int keyboard;
   unsigned int joysticks;
   int cycle_count;

   unsigned int scr_fs_width;
   unsigned int scr_fs_height;
   unsigned int scr_fs_bpp;
   unsigned int scr_style;
   unsigned int scr_oglfilter;
   unsigned int scr_vsync;
   unsigned int scr_led;
   unsigned int scr_fps;
   unsigned int scr_tube;
   unsigned int scr_intensity;
   unsigned int scr_phosphor_intensity;
   unsigned int scr_remanency;
   unsigned int scr_window;
   unsigned int scr_bpp;
   unsigned int scr_bps;
   unsigned int scr_line_offs;
   unsigned int *scr_base;
   unsigned int *scr_pos;
   void (*scr_render)(void);
   void (*scr_prerendernorm)(void);
   void (*scr_prerenderbord)(void);
   void (*scr_prerendersync)(void);
   void (*video_set_palette_antialias)(void);
   unsigned int (*rgb2color)(unsigned int r, unsigned int g, unsigned int b);
   bool scr_is_ogl;

   unsigned int snd_enabled;
   unsigned int snd_playback_rate;
   unsigned int snd_bits;
   unsigned int snd_stereo;
   unsigned int snd_volume;
   unsigned int snd_pp_device;
   unsigned int snd_buffersize;
   unsigned char *snd_bufferptr;

   unsigned int (*video_monitor)(double r, double g, double b);

   union
   {
#ifdef MSB_FIRST
      struct
      {
         unsigned int high;
         unsigned int low;
      };
#else
      struct
      {
         unsigned int low;
         unsigned int high;
      };
#endif
      int64_t both;
   } snd_cycle_count_init;

   unsigned int kbd_layout;

   unsigned int max_tracksize;
   char snap_path[_MAX_PATH + 1];
   char snap_file[_MAX_PATH + 1];
   bool snap_zip;
   char drvA_path[_MAX_PATH + 1];
   char drvA_file[_MAX_PATH + 1];
   bool drvA_zip;
   unsigned int drvA_format;
   char drvB_path[_MAX_PATH + 1];
   char drvB_file[_MAX_PATH + 1];
   bool drvB_zip;
   unsigned int drvB_format;
   char tape_path[_MAX_PATH + 1];
   char tape_file[_MAX_PATH + 1];
   bool tape_zip;
   char printer_file[_MAX_PATH + 1];
   char sdump_file[_MAX_PATH + 1];

   char rom_path[_MAX_PATH + 1];
   char rom_file[16][_MAX_PATH + 1];
#ifndef TARGET_GNW
   char rom_mf2[_MAX_PATH + 1];
#endif
} t_CPC;

typedef struct {
   unsigned int requested_addr;
   unsigned int next_addr;
   unsigned int addr;
   unsigned int next_address;
   unsigned int scr_base;
   unsigned int char_count;
   unsigned int line_count;
   unsigned int raster_count;
   unsigned int hsw;
   unsigned int hsw_count;
   unsigned int vsw;
   unsigned int vsw_count;
   unsigned int flag_hadhsync;
   unsigned int flag_inmonhsync;
   unsigned int flag_invsync;
   unsigned int flag_invta;
   unsigned int flag_newscan;
   unsigned int flag_reschar;
   unsigned int flag_resframe;
   unsigned int flag_resnext;
   unsigned int flag_resscan;
   unsigned int flag_resvsync;
   unsigned int flag_startvta;
   unsigned int last_hend;
   unsigned int reg5;
   unsigned int r7match;
   unsigned int r9match;
   unsigned int hstart;
   unsigned int hend;
   void (*CharInstMR)(void);
   void (*CharInstSL)(void);
   unsigned char reg_select;
   unsigned char registers[18];

   // 6128+ split screen support
   unsigned int split_addr;
   unsigned char split_sl;
   unsigned int sl_count;
   unsigned char interrupt_sl;
} t_CRTC;

typedef struct {
   int timeout;
   int motor;
   int led;
   int flags;
   int phase;
   int byte_count;
   int buffer_count;
   int cmd_length;
   int res_length;
   int cmd_direction;
   void (*cmd_handler)(void);
   unsigned char *buffer_ptr;
   unsigned char *buffer_endptr;
   unsigned char command[12];
   unsigned char result[8];
} t_FDC;

typedef struct {
	unsigned int hs_count;
   unsigned char ROM_config;
   unsigned char lower_ROM_bank;
   bool registerPageOn;
   unsigned char RAM_bank;
   unsigned char RAM_config;
   unsigned char upper_ROM;
   unsigned int requested_scr_mode;
   unsigned int scr_mode;
   unsigned char pen;
   unsigned char ink_values[17];
   unsigned int palette[34];
   unsigned char sl_count;
   unsigned char int_delay;
} t_GateArray;

typedef struct {
   unsigned char control;
   unsigned char portA;
   unsigned char portB;
   unsigned char portC;
} t_PPI;

typedef struct
{
   union
   {
      struct
      {
         #ifdef MSB_FIRST
         unsigned int high;
         unsigned int low;
         #else
         unsigned int low;
         unsigned int high;
         #endif
      };
      int64_t both;
   } cycle_count;

   unsigned int buffer_full;
   unsigned char control;
   unsigned char reg_select;
   union {
      unsigned char Index[16];
      struct {
         unsigned char TonALo, TonAHi;
         unsigned char TonBLo, TonBHi;
         unsigned char TonCLo, TonCHi;
         unsigned char Noise;
         unsigned char Mixer;
         unsigned char AmplitudeA, AmplitudeB, AmplitudeC;
         unsigned char EnvelopeLo, EnvelopeHi;
         unsigned char EnvType;
         unsigned char PortA;
         unsigned char PortB;
      };
   } RegisterAY;
   int AmplitudeEnv;
   bool FirstPeriod;
   void (*Synthesizer)(void);
} t_PSG;

typedef struct {
   int scrln;
   int scanline;
   unsigned int flag_drawing;
   unsigned int frame_completed;
} t_VDU;

typedef struct {
   union {
      unsigned char data[4];
      struct {
         unsigned char cylinder;
         unsigned char side;
         unsigned char sector_info;
         unsigned char sector_size;
      };
   } CHRN; // the CHRN for this sector
   unsigned char flags[4]; // ST1 and ST2 - reflects any possible error conditions
   unsigned char *data; // pointer to sector data
   unsigned int size; // sector size in bytes

   // weak sector support
   unsigned int weak_versions; // number of versions of this sector (should be 1 except for weak/random sectors)
   unsigned int weak_read_version; // version of the sector to return when reading
   unsigned int total_size; // total data size in bytes
} t_sector;

typedef struct {
   unsigned int sectors; // sector count for this track
   unsigned int size; // track size in bytes
   unsigned char *data; // pointer to track data
   t_sector sector[DSK_SECTORMAX]; // array of sector information structures
} t_track;

typedef struct {
   unsigned int tracks; // total number of tracks
   unsigned int current_track; // location of drive head
   unsigned int sides; // total number of sides
   unsigned int current_side; // side being accessed
   unsigned int current_sector; // sector being accessed
   unsigned int altered; // has the image been modified?
   unsigned int write_protected; // is the image write protected?
   unsigned int random_DEs; // sectors with Data Errors return random data?
   unsigned int flipped; // reverse the side to access?
   unsigned char *raw_data; // pointer to track data
   bool extended;
#ifndef TARGET_GNW
   t_track track[DSK_TRACKMAX][DSK_SIDEMAX]; // array of track information structures
#else
   t_track track; // array of track information structures
   int loaded_track; // location of drive head
   int loaded_side; // side being accessed
   bool is_compressed; // side being accessed
   unsigned char decompress_buffer[DSK_BPTMAX+0x100]; // Work buffer
#endif
} t_drive;

typedef struct {
   char *pchZipFile;
   char *pchExtension;
   char *pchFileNames;
   char *pchSelection;
   int iFiles;
   unsigned int dwOffset;
} t_zip_info;

#define MAX_DISK_FORMAT 8
#define DEFAULT_DISK_FORMAT 0
#define FIRST_CUSTOM_DISK_FORMAT 2
typedef struct {
   unsigned char label[40]; // label to display in options dialog
   unsigned int tracks; // number of tracks
   unsigned int sides; // number of sides
   unsigned int sectors; // sectors per track
   unsigned int sector_size; // sector size as N value
   unsigned int gap3_length; // GAP#3 size
   unsigned char filler_byte; // default byte to use
   unsigned char sector_ids[2][16]; // sector IDs
} t_disk_format;

// kbdauto.c
bool kbd_buf_update();
void kbd_buf_feed(char *s);
void vkbd_key(int key,int pressed);
int vkbd_key_state(int key);

// cap32.c
void caprice_retro_loop(void);
int capmain (int argc, char **argv);
void emulator_reset(bool bolMF2Reset);
void cap32_set_palette(int palette);
int video_set_palette (void);
void video_set_palette_antialias (void);
int emulator_select_ROM (void);
size_t get_ram_size(void);
void amstrad_set_audio_buffer(int8_t *buffer, uint32_t size);

// fdc.c
#ifdef __cplusplus
extern "C" {
#endif

int attach_disk_buffer(char *buffer, int drive);
int detach_disk(int drive);

unsigned char* sector_get_read_data(t_sector * sector);
void sector_set_sizes(t_sector * sector, unsigned int size, unsigned int total_size);

void cap32_check_unit(void);
void cap32_fdc_load_track(t_drive *drive,int load_track,int load_side);
void fdc_write_data(unsigned char val);
unsigned char fdc_read_status(void);
uint8_t fdc_read_data(void);

#ifdef __cplusplus
}
#endif

// psg.c
void SetAYRegister(int Num, unsigned char Value);
void Calculate_Level_Tables(void);
void ResetAYChipEmulation(void);
void InitAYCounterVars(void);
void InitAY(void);

#endif
