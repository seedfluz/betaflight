/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>

#include <platform.h>

#ifdef USE_PINIOBOX

#include "build/debug.h"

#include "common/utils.h"
#include "common/time.h"

#include "interface/msp_box.h"

#include "pg/pinio.h"
#include "pg/piniobox.h"

#include "piniobox.h"

static pinioBoxConfig_t pinioBoxRuntimeConfig;

void pinioBoxInit(const pinioBoxConfig_t *pinioBoxConfig)
{
    // Convert permanentId to boxId_e

    pinioBoxRuntimeConfig = *pinioBoxConfig;

    for (int i = 0; i < PINIO_COUNT; i++) {
        if (pinioBoxRuntimeConfig.boxId[i] >= 0) {
            const box_t *box = findBoxByPermanentId(pinioBoxRuntimeConfig.boxId[i]);
            if (box) {
                pinioBoxRuntimeConfig.boxId[i] = box->boxId;
            }
        }
    }
}

void pinioBoxUpdate(timeUs_t currentTimeUs)
{
    UNUSED(currentTimeUs);

    for (int i = 0; i < PINIO_COUNT; i++) {
        if (pinioBoxRuntimeConfig.boxId[i] >= 0) {
            pinioSet(i, getBoxIdState(pinioBoxRuntimeConfig.boxId[i]));
        }
    }
}

#endif
