/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package org.lineageos.sonygameboost;

import android.graphics.drawable.Icon;
import android.service.quicksettings.Tile;
import android.service.quicksettings.TileService;
import android.os.SystemProperties;
import android.widget.Toast;

import java.util.Timer;
import java.util.TimerTask;

import android.util.Log;

public class GameBoost extends TileService {
    protected static final String GAMEBOOST_ENABLED = "service.game.boost";
    private boolean mBoostDetection = false;

    @Override
    public void onStartListening() {
        super.onStartListening();
        refresh();
    }

    @Override
    public void onClick() {
        super.onClick();
        if (mBoostDetection) {
        SystemProperties.set(GAMEBOOST_ENABLED, "off");
        mBoostDetection = false;
        Log.d("GameBoost", "Stopped GameBoost");
        } else {
        SystemProperties.set(GAMEBOOST_ENABLED, "on");
        mBoostDetection = true;
        Log.d("GameBoost", "Starting GameBoost");
        Toast.makeText(GameBoost.this, getString(R.string.toast), Toast.LENGTH_LONG).show();
        }
        refresh();
    }

    private void refresh() {
        if (mBoostDetection) {
            getQsTile().setIcon(Icon.createWithResource(this, R.drawable.gameboost_on));
            getQsTile().setState(Tile.STATE_ACTIVE);
        } else {
            getQsTile().setIcon(Icon.createWithResource(this, R.drawable.gameboost_off));
            getQsTile().setState(Tile.STATE_INACTIVE);
        }
        getQsTile().updateTile();
    }

}
