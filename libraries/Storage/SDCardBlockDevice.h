/* ########################################################################## */
/* - File: SDCardBlockDevice.h
   - Copyright (c): 2023 Arduino srl.  All right reserved.
   - Author: Daniele Aimo (d.aimo@arduino.cc)

     This library is free software; you can redistribute it and/or
     modify it under the terms of the GNU Lesser General Public
     License as published by the Free Software Foundation; either
     version 2.1 of the License, or (at your option) any later version.

     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Lesser General Public License for more details.

     You should have received a copy of the GNU Lesser General Public
     License along with this library; if not, write to the Free Software
     Foundation, Inc.,51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA */
/* ########################################################################## */
#ifndef ARDUINO_SDMMC_FLASH_BLOCK_DEVICE
#define ARDUINO_SDMMC_FLASH_BLOCK_DEVICE

/* base class for block devices */
#include "blockDevice.h"

/* Arduino.h to include the defines of the flash type LP or HP*/
#include "Arduino.h"

#include "r_sdhi.h"
#include "r_dtc.h"

/* -------------------------------------------------------------------------- */
/* CLASS SDCardBlockDevice - to access micro internal flash                    */
/* -------------------------------------------------------------------------- */

class SDCardBlockDevice : public CBlockDevice {
private:
  BdAddr_t base_address;
  BdSize_t size;
  BdSize_t read_block_size;
  BdSize_t erase_block_size;
  BdSize_t write_block_size;
  bool is_address_correct(BdAddr_t add);
  sdhi_instance_ctrl_t  ctrl;
  sdmmc_cfg_t           cfg;
  dtc_instance_ctrl_t   dtc_ctrl;
  dtc_extended_cfg_t    dtc_ext_cfg;    
  transfer_info_t       dtc_info;
  transfer_cfg_t        dtc_cfg;
  transfer_instance_t   dtc_instance;
  pin_t ck;
  pin_t cmd;
  pin_t d0;
  pin_t d1;
  pin_t d2;
  pin_t d3;
  pin_t cd;
  pin_t wp;
  static bool initialized;
  static bool card_inserted;
  static void SDCardBlockDeviceCbk(sdmmc_callback_args_t *);
public:

  SDCardBlockDevice( pin_t _ck, 
                     pin_t _cmd, 
                     pin_t _d0, 
                     pin_t _d1, 
                     pin_t _d2, 
                     pin_t _d3,
                     pin_t _cd,
                     pin_t _wp);
  
  SDCardBlockDevice(SDCardBlockDevice const&) = delete;
  void operator=(SDCardBlockDevice const&) = delete;
  virtual ~SDCardBlockDevice(); 

  virtual int open() override;
  virtual int close() override;
  virtual int read(void *buffer, BdAddr_t addr, BdSize_t size) override;
  virtual int write(const void *buffer, BdAddr_t addr, BdSize_t size) override;
  virtual int erase(BdAddr_t addr, BdSize_t size) override;
  virtual BdSize_t getWriteBlockSize() const override;
  virtual BdSize_t getEraseBlockSize() const override;
  virtual BdSize_t getReadBlockSize() const override;
  virtual BdSize_t getTotalSize() const override;
};

#endif
