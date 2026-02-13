// whitelist.inc - DayZ Indonesia Whitelist Checker
// Integration dengan Discord Bot

#if defined _whitelist_included
    #endinput
#endif
#define _whitelist_included

#define WHITELIST_PATH "scriptfiles/Whitelist/"

/*
 * IsPlayerWhitelisted - Cek apakah player sudah whitelist
 * Return: 1 = Whitelist, 0 = Tidak whitelist
 */
stock IsPlayerWhitelisted(playerid) {
    new filename[128], playername[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playername, MAX_PLAYER_NAME);
    
    format(filename, sizeof(filename), "%s%s.txt", WHITELIST_PATH, playername);
    
    if(!fexist(filename)) {
        return 0;
    }
    return 1;
}

/*
 * GetPlayerWhitelistStatus - Dapatkan status whitelist
 * Return: 0 = Tidak ditemukan, 1 = Approved, 2 = Pending, 3 = Rejected
 */
stock GetPlayerWhitelistStatus(playerid) {
    new filename[128], playername[MAX_PLAYER_NAME];
    new line[512];
    new File:fh;
    new status[32] = "not_found";
    
    GetPlayerName(playerid, playername, MAX_PLAYER_NAME);
    format(filename, sizeof(filename), "%s%s.txt", WHITELIST_PATH, playername);
    
    if(!fexist(filename)) {
        return 0;
    }
    
    fh = fopen(filename, io_read);
    if(fh) {
        while(fread(fh, line)) {
            if(strfind(line, "\"status\"") != -1) {
                // Extract status value
                new pos = strfind(line, ":") + 1;
                while(line[pos] == ' ' || line[pos] == '\"') pos++;
                
                new endpos = pos;
                while(line[endpos] != '\"' && line[endpos] != ',' && line[endpos] != '}') endpos++;
                
                strmid(status, line, pos, endpos);
                break;
            }
        }
        fclose(fh);
    }
    
    if(strcmp(status, "approved", true) == 0) return 1;
    else if(strcmp(status, "pending", true) == 0) return 2;
    else if(strcmp(status, "rejected", true) == 0) return 3;
    return 0;
}

/*
 * GetPlayerDiscordUsername - Dapatkan Discord username player
 */
stock GetPlayerDiscordUsername(playerid, discord_username[], size) {
    new filename[128], playername[MAX_PLAYER_NAME];
    new line[512];
    new File:fh;
    
    GetPlayerName(playerid, playername, MAX_PLAYER_NAME);
    format(filename, sizeof(filename), "%s%s.txt", WHITELIST_PATH, playername);
    
    if(!fexist(filename)) {
        discord_username[0] = '\0';
        return 0;
    }
    
    fh = fopen(filename, io_read);
    if(fh) {
        while(fread(fh, line)) {
            if(strfind(line, "\"discord_username\"") != -1) {
                new pos = strfind(line, ":") + 1;
                while(line[pos] == ' ' || line[pos] == '\"') pos++;
                
                new endpos = pos;
                while(line[endpos] != '\"' && line[endpos] != ',') endpos++;
                
                strmid(discord_username, line, pos, endpos);
                fclose(fh);
                return 1;
            }
        }
        fclose(fh);
    }
    
    return 0;
}

/*
 * SendPlayerWhitelistStatus - Kirim pesan status whitelist ke player
 */
stock SendPlayerWhitelistStatus(playerid) {
    new status = GetPlayerWhitelistStatus(playerid);
    new playername[MAX_PLAYER_NAME];
    
    GetPlayerName(playerid, playername, MAX_PLAYER_NAME);
    
    switch(status) {
        case 0: {
            SendClientMessage(playerid, 0xFF0000FF, "[WHITELIST] Anda TIDAK terdaftar whitelist!");
            SendClientMessage(playerid, 0xFF0000FF, "[WHITELIST] Silakan daftar di Discord bot kami terlebih dahulu.");
        }
        case 1: {
            SendClientMessage(playerid, 0x00FF00FF, "[WHITELIST] Akun Anda sudah di-APPROVE! Selamat bermain.");
        }
        case 2: {
            SendClientMessage(playerid, 0xFFFF00FF, "[WHITELIST] Akun Anda masih PENDING approval.");
            SendClientMessage(playerid, 0xFFFF00FF, "[WHITELIST] Tunggu admin approve registrasi Anda.");
        }
        case 3: {
            SendClientMessage(playerid, 0xFF0000FF, "[WHITELIST] Akun Anda DITOLAK (Rejected)!");
            SendClientMessage(playerid, 0xFF0000FF, "[WHITELIST] Hubungi admin untuk info lebih lanjut.");
        }
    }
    return 1;
}
