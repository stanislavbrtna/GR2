/*
Copyright (c) 2022 Stanislav Brtna

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "GR2.h"
gr2context * svs_pscg_c;

void set_gr2_workaround_context(gr2context * c) {
  svs_pscg_c = c;
}


// workarounds for SVS string garbage collecotor
void gr2_garbage_workaround(uint8_t *strId, uint32_t str_len, uint8_t *max) {
  uint16_t x = 0;

  for(x = 1; x <= svs_pscg_c->maxElementsId; x++) {
      if (((svs_pscg_c->pscgElements[x].str_value) > strId)
            && (svs_pscg_c->pscgElements[x].str_value <= max)
            && (svs_pscg_c->pscgElements[x].valid == 1))
      {
        //printf("GR2-GC-DBG changing: %s \n", svs_pscg_c->pscgElements[x].str_value - (uint8_t *)str_len);
        svs_pscg_c->pscgElements[x].str_value
          = (void*) ((uint32_t)svs_pscg_c->pscgElements[x].str_value - str_len);
      }

      if (((svs_pscg_c->pscgElements[x].str_value2) > strId)
            && (svs_pscg_c->pscgElements[x].str_value2 <= max)
            && (svs_pscg_c->pscgElements[x].valid == 1))
      {
        //printf("GR2-GC-DBG changing: %s to %s\n", pscgElements[x].str_value,pscgElements[x].str_value - (uint8_t *)str_len);
        svs_pscg_c->pscgElements[x].str_value2
          = (void*) ((uint32_t)svs_pscg_c->pscgElements[x].str_value2 - str_len);
      }
  }
}


uint8_t gr2_garbage_workaround2(uint8_t *strId) {
  uint16_t x = 0;

  for(x = 1; x <= svs_pscg_c->maxElementsId; x++) {
      if ((svs_pscg_c->pscgElements[x].str_value == strId || svs_pscg_c->pscgElements[x].str_value2 == strId) && (svs_pscg_c->pscgElements[x].valid == 1)) {
        //printf("GR2-GC-DBG: valid string:%s", pscgElements[x].str_value);
        return 1;
      }
  }
  return 0;
}
