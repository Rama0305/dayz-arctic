
																///////////
														////////////////////////////
											////////////////////////////////////////////////////
                                  //////////////////////////                   //////////////////////////
                         ///////////////////////////////////     COMANDOS      /////////////////////////////////
                                  //////////////////////////                   //////////////////////////
											///////////////////////////////////////////////////
							                           //////////////////////////////
    														   	///////////

CMD:verinventarioid(playerid, params[])
{
	new id;
	if(sscanf(params, "u", id)) return ms(playerid, 2, "Usage: /viewinventoryid [ID/Nick].");
	if(!Online(id)) return ms(playerid, 0, "This player is not online!");
	String_Gigante[0] = EOS;
	new id_i;
	new uni_i;
	strcat(String_Gigante, "Slot\tName\tUnits\n");
	for(new i; i<MAX_SLOTS; i++)
	{
	    id_i = Inventario[id][i][inv_ID];
	    uni_i = Inventario[id][i][inv_Unidades];
	    strcat(String_Gigante, "{a1a1a1}");
		strcat(String_Gigante, ConvertMoney(i));
	    strcat(String_Gigante, "\t{ffffff}");
		strcat(String_Gigante, Itens[id_i][item_Nome]);
	    strcat(String_Gigante, "\t{ffff00}");
		strcat(String_Gigante, ConvertMoney(uni_i));
		strcat(String_Gigante, "\n");
	}
	new sss[150];
	format(sss, 150, "{ffffff}Inventario de {00ffff}%s", Nome(id));
	ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_STYLE_TABLIST_HEADERS, sss, String_Gigante, "Ok", "Fechar");
	return 1;
}

CMD:viewinventory(playerid, params[])
{
    new id[40];
    if(sscanf(params, "s[40]", id)) return ms(playerid, 2, "Usage: /viewinventory [ Nick ].");
    if(!ContaExiste(id)) return ms(playerid, 0, "This account does not exist!");
    new sss[150];
    if(IsPlayerOnline(id))
    {
        new idd = GetPlayerID(id);
        cmd_verinventarioid(playerid, ConvertMoney(idd));
        return 1;
    }
    new file[80];
    format(file, 80, "Inventarios/%s.txt", id);
    if(!DOF2_FileExists(file)) return ms(playerid, 0, "Database error occurred, please try again!");
    String_Gigante[0] = EOS;
    new id_i;
    new uni_i;
    strcat(String_Gigante, "Slot\tName\tQuantity\n");
    new string[100];
    for(new i; i<MAX_SLOTS; i++)
    {
        format(string, 100, "ID_%d", i);
        id_i = DOF2_GetInt(file, string);
        format(string, 100, "Unidades_%d", i);
        uni_i = DOF2_GetInt(file, string);
        strcat(String_Gigante, "{a1a1a1}");
        strcat(String_Gigante, ConvertMoney(i));
        strcat(String_Gigante, "\t{ffffff}");
        strcat(String_Gigante, Itens[id_i][item_Nome]);
        strcat(String_Gigante, "\t{ffff00}");
        strcat(String_Gigante, ConvertMoney(uni_i));
        strcat(String_Gigante, "\n");
    }
    format(sss, 150, "{ffffff}Inventory belonging to {00ffff}%s", id);
    ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_STYLE_TABLIST_HEADERS, sss, String_Gigante, "Ok", "Close");
    return 1;
}




CMD:jail(playerid, params[])
{
    new cont;
    new string[300];
    String_Gigante[0] = EOS;
    strcat(String_Gigante, "ID      Nama\tWaktu\tAdmin\tAlasan\n");
    for(new i; i<MAX_PLAYERS; i++)
    {
        if(pInfo[i][pCadeia] > 0)
        {
            format(string, 300, "{a1a1a1}%03d     {ffff00}%s\t{ffffff}%s\t%s\t\t{ffffff}%s\n", 
                i, Nome(i), ConvertTime(pInfo[i][pCadeia]), pInfo[i][pCadeiaAdmin], pInfo[i][pCadeiaMotivo]);
            strcat(String_Gigante, string);
            cont ++;
        }
    }
    format(string, 300, "{ffffff}Players currently serving punishment {a1a1a1}[%d]", cont);
    ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_STYLE_TABLIST_HEADERS, string, String_Gigante, "Ok", "Close");
    return 1;
}

CMD:destoryobject(playerid, params[])
{
    new cont;
    for(new i; i<MAX_OBJETOS; i++)
    {
        if(Obj[i][obj_Existe] == 1)
        {
            if(Obj[i][obj_Base] == -1)
            {
                cont++;
                destruir_objeto(i);
            }
        }
    }
    new str[200];
    format(str, 200, "Total %d objects without base have been destroyed!", cont);
    ms(playerid, 4, str);
    return 1;
}

CMD:ask(playerid, params[])
{
    if(GetPVarInt(playerid, "flood_duvida") > gettime()) return ms(playerid, 0, "You can only use this command every 15 seconds!");
    new moti[150];
    new str[200];
    if(sscanf(params, "s[150]", moti)) return ms(playerid, 2, "Usage: /ask [question content].");
    format(str, 200, "[PERTANYAAN] %s [%d]: %s", Nome(playerid), playerid, moti);
    new tem = msa(0x00FA9Aff, str);
    if(tem == 0) return ms(playerid, 0, "No admin is currently online in Work Mode!");
    format(str, 200, "Your question has been sent to Admin. Please wait for a response.");
    ms(playerid, 4, str);
    SetPVarInt(playerid, "flood_duvida", gettime() +15);
    return 1;
}


CMD:report(playerid, params[])
{
    if(GetPVarInt(playerid, "flood_report") > gettime()) return ms(playerid, 0, "You can only use this command every 15 seconds!");
    new i, moti[150];
    new str[200];
    if(sscanf(params, "us[150]",  i, moti)) return ms(playerid, 2, "Usage: /report [ID/Nick] [Reason].");
    if(!Online(i)) return ms(playerid, 0, "This player is not online!");
    format(str, 200, "[REPORT] %s[%d] is reporting {a1a1a1}%s[%d]{FF4500} reason: %s", Nome(playerid), playerid, Nome(i), i, moti);
    new tem = msa(0xFF4500ff, str);
    if(tem == 0) return ms(playerid, 0, "There is no admin currently online in Work Mode!");
    format(str, 200, "You have reported %s[%d]. Your message has been sent to Admin.", Nome(i), i);
    ms(playerid, 4, str);
    SetPVarInt(playerid, "flood_report", gettime() +15);
    return 1;
}

CMD:endhelp(playerid, params[])
{
    new str[150];
    if(atendimento_player[playerid] != -1)
    {
        new i = atendimento_player[playerid];
        format(str, 150, "Player %s has ended the help session. Duration: %s.", Nome(playerid), ConvertTime(gettime()-Atendimento[i][at_Atendido]));
        for(new pla; pla<MAX_PLAYERS; pla++)
        {
            if(atendimento_admin[pla] == i)
            {
                ms(pla, 4, str);
                new idadm = AdminID(pla);
                if(idadm != -1)
                {
                    Admin[idadm][adm_Atendimentos] ++;
                    atendimento_admin[pla] = -1;
                    salvar_admin(idadm);
                }
            }
        }
        format(str, 150, "You have ended the help session. Duration: %s.", ConvertTime(gettime()-Atendimento[i][at_Atendido]));
        ms(playerid, 4, str);
        destruir_atendimento(i);
        atendimento_player[playerid] = -1;
        return 1;
    }

    if(atendimento_admin[playerid] != -1)
    {
        new i = atendimento_admin[playerid];
        format(str, 150, "Admin %s has ended the help session. Duration: %s.", Nome(playerid), ConvertTime(gettime()-Atendimento[i][at_Atendido]));
        for(new pla; pla<MAX_PLAYERS; pla++) if(Online(pla)) if(atendimento_player[pla] == i) atendimento_player[pla] = -1, ms(pla, 4, str);
        new idadm = AdminID(playerid);
        if(idadm != -1)
        {
            Admin[idadm][adm_Atendimentos] ++;
            salvar_admin(idadm);
        }
        format(str, 150, "You have ended the help session. Duration: %s.", ConvertTime(gettime()-Atendimento[i][at_Atendido]));
        ms(playerid, 4, str);
        destruir_atendimento(i);
        atendimento_admin[playerid] = -1;
        return 1;
    }

    for(new ii; ii<MAX_ATENDIMENTOS; ii++)
    {
        if(Atendimento[ii][at_Existe] != 0)
        {
            if(Comparar(Nome(playerid), Atendimento[ii][at_Player]))
            {
                ms(playerid, 4, "You have cancelled the help request.");
                destruir_atendimento(ii);
                return 1;
            }
        }
    }

    ms(playerid, 0, "You are not in any help session right now!");
    return 1;
}

CMD:helpme(playerid, params[])
{
    if(AdminPlayer(playerid) > 0) return ms(playerid, 0, "You are an Admin, you cannot use this command!");
    new cont;
    for(new i; i<MAX_ATENDIMENTOS; i++)
    {
        if(Atendimento[i][at_Existe] != 0)
        {
            cont ++;
            if(Comparar(Nome(playerid), Atendimento[i][at_Player]))
            {
                ms(playerid, 0, "You have already requested help, please wait!");
                return 1;
            }
        }
    }
    if(cont == MAX_ATENDIMENTOS) return ms(playerid, 0, "Too many help requests at this time, please try again later!");
    ShowPlayerDialog_(playerid, DIALOG_ATENDIMENTO, DIALOG_STYLE_LIST, "Help Priority", "{00ff00}Low\n{ffff00}Medium\n{ff0000}High", "Submit", "Cancel");
    return 1;
}

CMD:accepthelp(playerid, params[])
{
    new i;
    new str[150];
    if(sscanf(params, "d",  i)) return ms(playerid, 2, "Usage: /accepthelp [Help ID (/helpme_list)].");
    if(i < 0 || i >= MAX_ATENDIMENTOS) return ms(playerid, 0, "Invalid help ID!");
    if(Atendimento[i][at_Existe] == 0) return ms(playerid, 0, "This help ID does not exist!");
    if(Atendimento[i][at_Existe] == 2) return ms(playerid, 0, "This help has already been handled by another admin!");
    for(new ii; ii<MAX_ATENDIMENTOS; ii++)
    {
        if(Atendimento[ii][at_Existe] != 0)
        {
            if(Comparar(Nome(playerid), Atendimento[ii][at_Admin]))
            {
                ms(playerid, 0, "You are already handling another help request!");
                return 1;
            }
        }
    }

    if(IsPlayerOnline(Atendimento[i][at_Player]))
    {
        new id = GetPlayerID(Atendimento[i][at_Player]);
        if(Online(id))
        {
            Atendimento[i][at_Existe] = 2;
            Atendimento[i][at_Atendido] = gettime();
            format(Atendimento[i][at_Admin], MAX_PLAYER_NAME, Nome(playerid));
            format(str, 150, "Admin %s accepted your help request. Please use chat to communicate.", Nome(playerid));
            ms(id, 4, str);
            format(str, 150, "You accepted a help request from %s. Please use chat to communicate.", Nome(id));
            ms(playerid, 4, str);
            format(str, 150, "Help session started. Waiting time: %s.", ConvertTime(gettime()-Atendimento[i][at_Iniciado]));
            ms(playerid, 4, str);
            ms(id, 4, str);
            atendimento_admin[playerid] = i;
            atendimento_player[id] = i;
            ms(playerid, 4, "Use /endhelp to end the help session.");
            ms(id, 4, "Use /endhelp to end the help session.");
            return 1;
        }
    }

    ms(playerid, 0, "The player who requested help is no longer online!");
    return 1;
}

CMD:listhelp(playerid, params[])
{
    mostrar_atendimentos(playerid);
    return 1;
}

CMD:bases(playerid, params[])
{
    mostrar_bases(playerid);
    return 1;
}

CMD:bringchest(playerid, params[])
{
    new i;
    if(sscanf(params, "d",  i)) return ms(playerid, 2, "Usage: /bringchest [Base ID].");
    if(i < 0 || i > MAX_BASES) return ms(playerid, 2, "Invalid base ID!");
    if(Base[i][base_Existe] == 0) return ms(playerid, 2, "This base does not exist!");
    for(new b; b<MAX_BAUS; b++)
    {
        if(Bau[b][bau_Existe] == 0) continue;
        if(Bau[b][bau_Base] == i)
        {
            new Float:pos[4];
            GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
            GetPlayerFacingAngle(playerid, pos[3]);
            PegarFrente(pos[0], pos[1], pos[3], -1.5);
            Bau[b][bau_X] = pos[0];
            Bau[b][bau_Y] = pos[1];
            Bau[b][bau_Z] = pos[2];
            Bau[b][bau_RZ] = pos[3];
            atualizar_bau(b);
            ms(playerid, 3, "You have moved the Chest from this base.");
            return 1;
        }
    }
    ms(playerid, 0, "This base does not have a Material Chest!");
    return 1;
}

CMD:bringtable(playerid, params[])
{
    new i;
    if(sscanf(params, "d",  i)) return ms(playerid, 2, "Usage: /bringtable [Base ID].");
    if(i < 0 || i > MAX_BASES) return ms(playerid, 2, "Invalid base ID!");
    if(Base[i][base_Existe] == 0) return ms(playerid, 2, "This base does not exist!");
    for(new b; b<MAX_MESAS; b++)
    {
        if(Mesa[b][me_Existe] == 0) continue;
        if(Mesa[b][me_Base] == i)
        {
            new Float:pos[4];
            GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
            GetPlayerFacingAngle(playerid, pos[3]);
            PegarFrente(pos[0], pos[1], pos[3], -1.5);
            Mesa[b][me_X] = pos[0];
            Mesa[b][me_Y] = pos[1];
            Mesa[b][me_Z] = pos[2];
            Mesa[b][me_RZ] = pos[3];
            atualizar_mesa(b);
            ms(playerid, 3, "You have moved the Craft Table from this base.");
            return 1;
        }
    }
    ms(playerid, 0, "This base does not have a Craft Table!");
    return 1;
}

CMD:bringrecycler(playerid, params[])
{
    new i;
    if(sscanf(params, "d",  i)) return ms(playerid, 2, "Usage: /bringrecycler [Base ID].");
    if(i < 0 || i > MAX_BASES) return ms(playerid, 2, "Invalid base ID!");
    if(Base[i][base_Existe] == 0) return ms(playerid, 2, "This base does not exist!");
    for(new b; b<MAX_RECICLADORAS; b++)
    {
        if(Recicladora[b][re_Existe] == 0) continue;
        if(Recicladora[b][re_Base] == i)
        {
            new Float:pos[4];
            GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
            GetPlayerFacingAngle(playerid, pos[3]);
            PegarFrente(pos[0], pos[1], pos[3], -1.5);
            Recicladora[b][re_X] = pos[0];
            Recicladora[b][re_Y] = pos[1];
            Recicladora[b][re_Z] = pos[2];
            Recicladora[b][re_RZ] = pos[3];
            atualizar_recicladora(b);
            ms(playerid, 3, "You have moved the Recycler from this base.");
            return 1;
        }
    }
    ms(playerid, 0, "This base does not have a Recycler!");
    return 1;
}


CMD:admins(playerid, params[])
{
	new cont;
	new string[300];
	new modoo[50];
	String_Gigante[0] = EOS;
	strcat(String_Gigante, "ID    Name\tRole\tSessions\tMode\n");

	for(new i; i<MAX_ADMINS; i++)
	{
        Lista_Admins[playerid][i] = -1;
		if(Admin[i][adm_Existe] == 1)
		{
		    if(IsPlayerOnline(Admin[i][adm_Nome]))
		    {
		        new id = GetPlayerID(Admin[i][adm_Nome]);
		        if(ModoAdmin[id] == 0) format(modoo, 50, "{ff0000}Game");
		        else format(modoo, 50, "{ffff00}Work");
		        format(string, 300, "{a1a1a1}%03d   {ffffff}%s\t{00ffff}%s\t{ffffff}%d\t%s\n", id, Nome(id), Admin[i][adm_Funcao], Admin[i][adm_Atendimentos], modoo);
		        strcat(String_Gigante, string);
				Lista_Admins[playerid][cont] = id;
		        cont ++;
		    }
		}
	}
    ShowPlayerDialog_(playerid, DIALOG_ADMINS, DIALOG_STYLE_TABLIST_HEADERS, "Admins Online", String_Gigante, "Continue", "Close");
	return 1;
}

CMD:editobject(playerid, params[])
{
    new line[100];
    new count = 0;
    new Float:dist;
    new Float:pos[3];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    String_Gigante[0] = EOS;
    strcat(String_Gigante, "Object\tHealth\tDistance\n");
    
    SetPVarInt(playerid, "base", -1234);
    
    for(new ia = 0; ia < MAX_OBJETOS; ia++)
    {
        Objetos_Proximos[playerid][ia] = -1;
        if(count == 50) break;
        if(Obj[ia][obj_Existe] == 1)
        {
            if(IsPlayerInRangeOfPoint(playerid, 25, Obj[ia][obj_X], Obj[ia][obj_Y], Obj[ia][obj_Z]))
            {
                GetDistance(dist, pos[0], pos[1], pos[2], Obj[ia][obj_X], Obj[ia][obj_Y], Obj[ia][obj_Z]);
                format(line, 100, "%s\t%d%%\t%.0f meter(s)\n", 
                    Objetos[Obj[ia][obj_ID]][obj_Nome], Obj[ia][obj_Vida], dist);
                
                strcat(String_Gigante, line);
                Objetos_Proximos[playerid][count] = ia;
                count++;
            }
        }
    }

    format(line, 100, "{ffffff}Objects within 25 meters from you [{a1a1a1}%d{ffffff}]", count);  // kalimat notifikasi pakai bahasa Inggris karena setara UI umum
    ShowPlayerDialog_(playerid, DIALOG_BASE10, DIALOG_STYLE_TABLIST_HEADERS, line, String_Gigante, "Continue", "Cancel");
    return 1;
}



CMD:platform(playerid, params[])
{
    ShowPlayerDialog_(playerid, DIALOG_PLATAFORMA, DIALOG_STYLE_MSGBOX, "Select Platform",
        "\n\n{ffffff}ATTENTION: {a1a1a1}To continue {ffffff}Login {a1a1a1}to the {ffffff}Server, {a1a1a1}we need you\nto tell us if you are playing on PC or on Mobile, please\nselect the appropriate option below:\n\n",
        "ANDROID", "PC");
    return 1;
}

CMD:flashlight(playerid, params[])
{
    if(Modo[playerid] != 1) 
        return ms(playerid, 0, "You are not in Story Mode!");
    if(!tem_item(playerid, 33)) 
        return ms(playerid, 0, "You do not have a Flashlight in your Inventory!");
    if(selecionando[playerid] == 1) 
        OnPlayerClickTextDraw(playerid, Text:INVALID_TEXT_DRAW);
    if(lanterna_player[playerid] == 1) 
        retirar_lanterna(playerid);
    else 
        colocar_lanterna(playerid);
    return 1;
}

CMD:tv(playerid, params[])
{
    new id;
    new msg[150];

    if(sscanf(params, "u", id))
    {
        if(tv_player[playerid] != -1)
        {
            TogglePlayerSpectating(playerid, false);
            ms(playerid, 1, "You exited TV Mode.");
            SetPlayerPos(playerid, pInfo[playerid][pX], pInfo[playerid][pY], pInfo[playerid][pZ]);
            SetPlayerFacingAngle(playerid, pInfo[playerid][pA]);
            SetPlayerInterior(playerid, pInfo[playerid][pInterior]);
            SetPlayerVirtualWorld(playerid, pInfo[playerid][pMundo]);
            tv_player[playerid] = -1;
            esconder_tv(playerid);
            carregarconta(playerid);
            return 1;
        }
        ms(playerid, 2, "Usage: /tv [ID/Name].");
        return 1;
    }

    if(!Online(id))
        return ms(playerid, 0, "This player is not Online!");
    if(id == playerid)
        return ms(playerid, 0, "You cannot spy on yourself!");
    if(tv_player[id] != -1)
        return ms(playerid, 0, "This player is in /tv mode watching someone else!");

    if(tv_player[playerid] == -1)
    {
        GetPlayerPos(playerid, pInfo[playerid][pX], pInfo[playerid][pY], pInfo[playerid][pZ]);
        GetPlayerFacingAngle(playerid, pInfo[playerid][pA]);
        pInfo[playerid][pInterior] = GetPlayerInterior(playerid);
        pInfo[playerid][pMundo] = GetPlayerVirtualWorld(playerid);
        salvarplayer(playerid);
    }

    tv_player[playerid] = id;
    mostrar_tv(playerid);
    SetPlayerInterior(playerid, GetPlayerInterior(id));
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(id));
    TogglePlayerSpectating(playerid, true);

    if(!IsPlayerInAnyVehicle(id)) 
        PlayerSpectatePlayer(playerid, id);
    else 
        PlayerSpectateVehicle(playerid, GetPlayerVehicleID(id));
    
    format(msg, 150, "You are watching: %s[%d], use /tv to return to your position.", Nome(id), id);
    ms(playerid, 1, msg);
    return 1;
}




CMD:teleports(playerid, params[])
{
    mostrar_teleportes(playerid);
    return 1;
}

CMD:listadmins(playerid, params[])
{
    mostrar_admins(playerid);
    return 1;
}

CMD:chatkill(playerid, params[])
{
    ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_STYLE_LIST, "{ffffff}[ {a1a1a1}Chat Kill Mode Cerita {ffffff}]", ler_log_kills(), "Ok", "Tutup");
    return 1;
}

CMD:showcombats(playerid, params[])
{
    ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_STYLE_LIST, "{ffffff}[ {a1a1a1}Pertempuran Terakhir {ffffff}]", ler_log_combates(), "Ok", "Tutup");
    return 1;
}

CMD:logs(playerid, params[])
{
    mostrar_logs(playerid);
    return 1;
}

CMD:respawntime(playerid, params[])
{
    new time;
    if(sscanf(params, "d", time)) return ms(playerid, 2, "Use: /respawntime [ minutes ].");
    if(time < 1) return ms(playerid, 0, "Use a time greater than 0 minutes!");
    new msg[200];
    time = time * 60;
    tempo_respawn = time;
    respawn_auto = tempo_respawn;
    format(msg, 200, "You have changed the automatic respawn time to [%s].", ConvertTime(time));
    ms(playerid, 3, msg);
    salvar_configuracoes();
    return 1;
}

CMD:lootdistance(playerid, params[])
{
    new distance;
    if(sscanf(params, "d", distance)) return ms(playerid, 2, "Use: /lootdistance [ jarak dalam meter ].");
    if(distance < 1) return ms(playerid, 0, "Gunakan nilai lebih dari 0 meter!");
    new msg[200];
    distancia_loot = distance;
    format(msg, 200, "You have changed the loot chest visibility distance on the map to [%s] meters.", ConvertMoney(distance));
    ms(playerid, 3, msg);
    salvar_configuracoes();
    for(new i; i < MAX_LOOT; i++) if(Loot[i][loot_Existe] == 1) atualizar_loot(i);
    return 1;
}

CMD:info(playerid, params[])
{
    new id;
    if(sscanf(params, "u", id)) return ms(playerid, 2, "Use: /info [ ID/Nick ].");
    if(!Online(id)) return ms(playerid, 0, "This player is not Online.");
    String_Gigante[0] = EOS;

    strcat(String_Gigante, "\n\n\n{ffffff}ID: {a1a1a1}");
    strcat(String_Gigante, ConvertMoney(id));
    strcat(String_Gigante, "\n{ffffff}Nick: {a1a1a1}");
    strcat(String_Gigante, Nome(id));
    strcat(String_Gigante, "{ffffff}\nPlatform: {a1a1a1}");
    strcat(String_Gigante, Prataforma(id));
    strcat(String_Gigante, "{ffffff}\nMode: {a1a1a1}");
    strcat(String_Gigante, ModoPlayer(id));
    strcat(String_Gigante, "\n{ffffff}Level: {ffff00}");
    strcat(String_Gigante, ConvertMoney(pInfo[id][pLevel]));

    if(pInfo[id][pClasse] == -1) strcat(String_Gigante, "{ffffff}\nClass: {a1a1a1}None");
    else
    {
        strcat(String_Gigante, "{ffffff}\nKelas: {a1a1a1}");
        strcat(String_Gigante, Classes[pInfo[id][pClasse]][classe_Nome]);
    }
    if(BasePlayer(id) == -1) strcat(String_Gigante, "{ffffff}\nBase: {a1a1a1}None");
    else
    {
        strcat(String_Gigante, "{ffffff}\nBasis: {a1a1a1}");
        strcat(String_Gigante, Base[BasePlayer(id)][base_Nome]);
    }

    strcat(String_Gigante, "\n{ffffff}Zombie Mati: {00ffff}");
    strcat(String_Gigante, ConvertMoney(pInfo[id][pZombies]));
    strcat(String_Gigante, "\n{ffffff}Membunuh: {00ffff}");
    strcat(String_Gigante, ConvertMoney(pInfo[id][pMatou]));
    strcat(String_Gigante, "\n{ffffff}Mati: {00ffff}");
    strcat(String_Gigante, ConvertMoney(pInfo[id][pMorreu]));

    if(lstream[playerid] != SV_NULL) strcat(String_Gigante, "{ffffff}\nVoip: {00ff00}On");
    else strcat(String_Gigante, "{ffffff}\nVoip: {ff0000}Off");
    strcat(String_Gigante, "\n\n\n");

    ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_STYLE_MSGBOX, "Informasi", String_Gigante, "Ok", "Tutup");
    return 1;
}


CMD:waktu(playerid, params[])
{
	if(AdminPlayer(playerid) == 0) return ms(playerid, 0, "You are not an admin!");
    new str[150];
    format(str, 150, "Server has been running for %s.", ConvertTime(tempo_ligado));
    ms(playerid, 4, str);
    return 1;
}


CMD:cuaca(playerid, params[])
{
	if(AdminPlayer(playerid) == 0) return ms(playerid, 0, "Anda bukan admin!");
	mostrar_climas(playerid);
	return 1;
}


CMD:destroyrecycle(playerid, params[])
{
	new ida;
	new str[150];
	if(sscanf(params, "d", ida)) return ms(playerid, 2, "Usage: /destroyrecycler [id].");
	if(ida < 0 || ida >= MAX_RECICLADORAS) return ms(playerid, 0, "Recycler ID is not valid!");
	if(Recicladora[ida][re_Existe] == 0) return ms(playerid, 0, "Recycler ID is not valid!");
	destruir_recicladora(ida);
	format(str, 150, "Admin '%s' destroyed Recycler ID: %d.", Nome(playerid), ida);
	for(new i; i < MAX_PLAYERS; i++) if(Online(i)) if(Modo[i] == 1) ms(i, 3, str);
	return 1;
}


CMD:destroychest(playerid, params[])
{
    new ida;
    new str[150];
    if(sscanf(params, "d", ida)) return ms(playerid, 2, "Usage: /destroychest [ id ].");
    if(ida < 0 || ida >= MAX_BAUS) return ms(playerid, 0, "Invalid Material Chest ID!");
    if(Bau[ida][bau_Existe] == 0) return ms(playerid, 0, "Invalid Material Chest ID!");
    destruir_bau(ida);
    format(str, 150, "Admin '%s' destroyed the Material Chest ID: %d.", Nome(playerid), ida);
    for(new i; i<MAX_PLAYERS; i++) if(Online(i)) if(Modo[i] == 1) ms(i, 3, str);
    return 1;
}
CMD:destroytable(playerid, params[])
{
    new ida;
    new str[150];
    if(sscanf(params, "d", ida)) return ms(playerid, 2, "Usage: /destroytable [ id ].");
    if(ida < 0 || ida >= MAX_MESAS) return ms(playerid, 0, "Invalid Crafting Table ID!");
    if(Mesa[ida][me_Existe] == 0) return ms(playerid, 0, "Invalid Crafting Table ID!");
    destruir_mesa(ida);
    format(str, 150, "Admin '%s' destroyed the Crafting Table ID: %d.", Nome(playerid), ida);
    for(new i; i<MAX_PLAYERS; i++) if(Online(i)) if(Modo[i] == 1) ms(i, 3, str);
    return 1;
}
CMD:destroybox(playerid, params[])
{
    new ida;
    new str[150];
    if(sscanf(params, "d", ida)) return ms(playerid, 2, "Usage: /destroybox [ id ].");
    if(ida < 0 || ida >= MAX_CAIXAS) return ms(playerid, 0, "Invalid Item Box ID!");
    if(Caixa[ida][caixa_Existe] == 0) return ms(playerid, 0, "Invalid Item Box ID!");
    destruir_caixa(ida);
    format(str, 150, "Admin '%s' destroyed the Item Box ID: %d.", Nome(playerid), ida);
    for(new i; i<MAX_PLAYERS; i++) if(Online(i)) if(Modo[i] == 1) ms(i, 3, str);
    return 1;
}

CMD:destroygate(playerid, params[])
{
    new ida;
    new str[150];
    if(sscanf(params, "d", ida)) return ms(playerid, 2, "Usage: /destroygate [ id ].");
    if(ida < 0 || ida >= MAX_PORTOES) return ms(playerid, 0, "Invalid gate ID!");
    if(Portao[ida][portao_Existe] == 0) return ms(playerid, 0, "Invalid gate ID!");
    destruir_portao(ida);
    format(str, 150, "Admin '%s' destroyed gate ID: %d.", Nome(playerid), ida);
    for(new i; i<MAX_PLAYERS; i++) if(Online(i)) if(Modo[i] == 1) ms(i, 3, str);
    return 1;
}

CMD:detonator(playerid, params[])
{
    if(!Haid() && ModoAdmin[playerid] == 0) return ms(playerid, 0, "You cannot use this item at the moment, use /help > Haid Schedules.");
    if(Modo[playerid] != 1) return ms(playerid, 0, "You are not in Story Mode!");
    if(!tem_item(playerid, 55)) return ms(playerid, 0, "You do not have a Detonator in your Inventory!");
    if(Barra[playerid][b_Acao] != 0) return ms(playerid, 0, "Your hands are busy, please wait and try again!");
    explosivos_player(playerid);
    format(string_prox, 300, " The player %s picked up an explosives detonator ", Nome(playerid));
    ProxDetector(10.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
    return 1;
}

CMD:map(playerid, params[])
{
    if(Modo[playerid] != 1) return ms(playerid, 0, "You are not in Story Mode!");
    if(!tem_item(playerid, 107)) return ms(playerid, 0, "You do not have a Map in your Inventory!");
    if(Barra[playerid][b_Acao] != 0) return ms(playerid, 0, "Your hands are busy, please wait and try again!");
    if(selecionando[playerid] == 1) OnPlayerClickTextDraw(playerid, Text:INVALID_TEXT_DRAW);
    mostrar_mapa(playerid);
    format(string_prox, 300, " The player %s opened their Map ", Nome(playerid));
    ProxDetector(10.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
    return 1;
}

CMD:notebook(playerid, params[])
{
    if(EmCombate(playerid)) return ms(playerid, 0, "You cannot do this in Combat!");
    if(tv_player[playerid] != -1) return ms(playerid, 0, "You cannot do this in /tv Mode!");
    if(olhando_camera[playerid] != -1) return ms(playerid, 0, "You are currently observing a camera!");
    if(Modo[playerid] != 1) return ms(playerid, 0, "You are not in Story Mode!");
    if(GetPlayerInterior(playerid) != 0) return ms(playerid, 0, "You cannot do this indoors!");
    if(!tem_item(playerid, 114)) return ms(playerid, 0, "You do not have a Notebook in your Inventory!");
    if(Barra[playerid][b_Acao] != 0) return ms(playerid, 0, "Your hands are busy, please wait and try again!");
    abrir_laptop(playerid, 0);
    return 1;
}



CMD:gps(playerid, params[])
{
    if(!tem_item(playerid, 108)) return ms(playerid, 0, "You do not have a Map in your Inventory!");
    if(gps_player[playerid] == 0)
    {
        if(player_gps[playerid] > 30)
        {
            GZ_EsconderGzPlayer(playerid, GZ_PRETA);
            gps_player[playerid] = 1;
            format(string_prox, 300, " Player %s turned on their GPS ", Nome(playerid));
            ProxDetector(15.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
            GameTextForPlayer(playerid, "~g~~h~~h~GPS ON", 1500, 3);
        }
        else ms(playerid, 0, "The GPS does not have enough battery, please try again later!");
    }
    else
    {
        gps_player[playerid] = 0;
        GZ_MostrarGzPlayer(playerid, GZ_PRETA);
        format(string_prox, 300, " Player %s turned off their GPS ", Nome(playerid));
        ProxDetector(15.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
        GameTextForPlayer(playerid, "~R~GPS OFF", 1500, 3);
    }

    return 1;
}

CMD:repair(playerid, params[])
{
    if(pInfo[playerid][pClasse] != 2) return ms(playerid, 0, "Command exclusive to the Mechanic class!");
    new Float:p[4];
    for(new v; v<MAX_VEHICLES; v++)
    {
        if(GetVehicleModel(v) != 0)
        {
            GetVehiclePos(v, p[0], p[1], p[2]);
            GetVehicleZAngle(v, p[3]);
            PegarFrente(p[0], p[1], p[3], -2.5);

            if(IsPlayerInRangeOfPoint(playerid, 2.5, p[0], p[1], p[2]))
            {
                if(VeiculoBicicleta(v)) continue;
                new engine, lights, alarm, doors, bonnet, boot, objective;
                GetVehicleParamsEx(v, engine, lights, alarm, doors, bonnet, boot, objective);
                new Float:vidacarro;
                GetVehicleHealth(v, vidacarro);
                if(vidacarro >= 950.0) return ms(playerid, 0, "This vehicle's engine is already in good condition.");
                if(!VeiculoBicicleta(v) && !VeiculoMoto(v) && !VeiculoBarco(v) && !VeiculoAviao2(v) && !VeiculoAviao(v))
                {
                    if(bonnet == 0)
                    {
                        ms(playerid, 0, "The /hood of this vehicle needs to be open, open it and try again.");
                        return 1;
                    }
                }

                if(Barra[playerid][b_Acao] == 0)
                {
                    SetPVarInt(playerid, "veiculo", v);
                    Acao(playerid, 10, 100, "REPAIRING ENGINE", 1, "BD_FIRE", "WASH_UP", 1);
                    SetPlayerAttachedObject(playerid, 9, 18644, 6, 0.107000, 0.010999, 0.000000,   0.000000, -136.500030, 0.000000,   1.000000, 1.000000, 1.000000);
                    GetVehiclePos(v, p[0], p[1], p[2]);
                    SetPlayerFacingAngle(playerid, GetPlayerAngleToPoint(playerid, p[0],p[1]));
                    SetVehicleParamsEx(v, 0, 0, alarm, doors, bonnet, boot, objective);
                }
                return 1;
            }
        }
    }

    ms(playerid, 0, "Use this box in front of a vehicle with the /hood open to repair it.");
    return 1;
}


CMD:setcash(playerid, params[])
{
    new cash, id;
    if(sscanf(params, "ud", id, cash)) return ms(playerid, 2, "Usage: /setcash [ ID/Nick ] [ Cash ].");
    if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
    if(cash < 0 ) return ms(playerid, 0, "Use a Cash value greater than or equal to 0!");
    new str[150];
    format(str, 150, "You set '%s's Cash to %s.", Nome(id), ConvertMoney(cash));
    ms(playerid, 3, str);
    format(str, 150, "Admin '%s' set your Cash to %s.", Nome(playerid), ConvertMoney(cash));
    ms(id, 3, str);
    pInfo[id][pCash] = cash;
    format(str, 150, "Admin '%s' set [%s] as the Cash for '%s'", Nome(playerid), ConvertMoney(cash), Nome(id));
    escrever_log_cash(str);
    return 1;
}
CMD:vpnsignup(playerid, params[])
{
    new ca;
    if(sscanf(params, "d", ca)) return ms(playerid, 2, "Usage: /vpnsignup [ Signup ID ].");
    if(ca < 0 || ca >= MAX_CADASTROS ) return ms(playerid, 0, "Invalid signup ID!");
    if(Cadastros[ca][cadastro_Existe] == 0) return ms(playerid, 0, "This signup does not exist!");
    if(Cadastros[ca][cadastro_VPN] == 0)
    {
        Cadastros[ca][cadastro_VPN] = 1;
        GameTextForPlayer(playerid, "~w~ANT VPN~n~~r~DEACTIVATED", 1000, 3);
    }
    else
    {
        Cadastros[ca][cadastro_VPN] = 1;
        GameTextForPlayer(playerid, "~w~ANT VPN~n~~g~ACTIVATED", 1000, 3);
    }
    salvar_cadastro(ca);
    return 1;
}


CMD:givecash(playerid, params[])
{
    new cash, id;
    if(sscanf(params, "ud", id, cash)) return ms(playerid, 2, "Usage: /givecash [ ID/Nick ] [ Cash ].");
    if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
    if(cash < 1 ) return ms(playerid, 0, "Use a Cash value greater than 0!");
    new str[150];
    format(str, 150, "You gave %s Cash to '%s'.", ConvertMoney(cash), Nome(id));
    ms(playerid, 3, str);
    format(str, 150, "Admin '%s' gave you %s Cash", Nome(playerid), ConvertMoney(cash));
    ms(id, 3, str);
    pInfo[id][pCash] += cash;
    format(str, 150, "Admin '%s' gave [%s] Cash to '%s'", Nome(playerid), ConvertMoney(cash), Nome(id));
    escrever_log_cash(str);
    return 1;
}


CMD:world(playerid, params[])
{
    new str[150];
    format(str, 150, "World: %d.", GetPlayerVirtualWorld(playerid));
    ms(playerid, 3, str);
    return 1;
}

CMD:interior(playerid, params[])
{
    if(Android[playerid] == 1)
    {
        new str[150];
        format(str, 150, "Interior: %d.", GetPlayerInterior(playerid));
        ms(playerid, 3, str);
    }
    return 1;
}

CMD:airdrop(playerid, params[])
{
    ms(playerid, 1, "You forced an Air Drop in a random location, please wait. Do not use this command too frequently!");
    proximo_drop = 1;
    return 1;
}


CMD:pay(playerid, params[])
{
    if(Modo[playerid] != 1) return ms(playerid, 0, "You can only use this command in Story Mode!");
    new id;
    new valor;
    if(sscanf(params, "ud", id, valor)) return ms(playerid, 2, "Usage: /pay [ ID/Nick ] [ R$ Amount ].");
    if(id == playerid) return ms(playerid, 0, "You cannot pay yourself!");
    if( valor <= 0 ) return ms(playerid, 0, "Use a value greater than 0!");
    if( valor > GranaPlayer(playerid)) return ms(playerid, 0, "You do not have that money in hand!");
    if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
    if(Modo[id] != 1) return ms(playerid, 0, "This player is not in Story Mode");
    new Float:pos[3];
    GetPlayerPos(id, pos[0], pos[1], pos[2]);
    if(GetPlayerInterior(playerid) != GetPlayerInterior(id)) return ms(playerid, 0, "You need to be near this player!");
    if(GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(id)) return ms(playerid, 0, "You need to be near this player!");
    if(!IsPlayerInRangeOfPoint(playerid, 20, pos[0], pos[1], pos[2])) return ms(playerid, 0, "You need to be near this player!");
    format(string_prox, 300, " Player %s paid R$ %s to %s ", Nome(playerid), ConvertMoney(valor), Nome(id));
    ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
    SetarGrana(playerid, GranaPlayer(playerid)-valor);
    SetarGrana(id, GranaPlayer(id)+valor);
    return 1;
}
CMD:rg(playerid, params[])
{
    if(pInfo[playerid][pConfig][0] == 1) return ms(playerid, 0, "You have disabled this chat in /settings!");
    new sss[300], id, mens[150];
    if(sscanf(params, "us[150]", id, mens)) return ms(playerid, 2, "Usage: /rg [ ID/Nick ] [ Message ]. Reply to someone in the global chat!");
    if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
    format(sss, 300, "Global {a1a1a1}%s[%d]: {ffff00}@%s {a1a1a1}- %s", Nome(playerid), playerid, Nome(id), mens);
    for(new i; i<MAX_PLAYERS; i++)
    {
        if(Online(i))
        {
            if(Modo[i] == 1)
            {
                if(pInfo[i][pConfig][0] == 0)
                {
                    if(ModoAdmin[playerid] == 0) SendClientMessage(i, 0x00ffffff, sss);
                    else SendClientMessage(i, 0xFFB6C1ff, sss);
                }
            }
        }
    }
    return 1;
}

CMD:global(playerid, params[]) return cmd_g(playerid, params);
CMD:g(playerid, params[])
{
    if(pInfo[playerid][pConfig][0] == 1) return ms(playerid, 0, "You have disabled this chat in /settings!");
    if(ModoAdmin[playerid] == 0 && !tem_item(playerid, 100)) return ms(playerid, 0, "You do not have a Radio Communicator in your Inventory!");
    if(AdminPlayer(playerid) == 0) if(GetPVarInt(playerid, "flood_global") > gettime()) return ms(playerid, 0, "You can only use this chat every 2 minutes!");
    new sss[300], mens[150];
    if(sscanf(params, "s[150]", mens)) return ms(playerid, 2, "Usage: /g [ Message ]. Story mode chat, use it to ask questions!");
    format(sss, 300, "Global {a1a1a1}%s[%d]: %s", Nome(playerid), playerid, mens);
    new radii = id_radio(playerid);
    if(ModoAdmin[playerid] == 0) if(radii == -1) return ms(playerid, 0, "You do not have a radio communicator in your Inventory!");
    for(new i; i<MAX_PLAYERS; i++)
    {
        if(Online(i))
        {
            if(Modo[i] == 1)
            {
                if(pInfo[i][pConfig][0] == 0)
                {
                    if(ModoAdmin[playerid] == 0) SendClientMessage(i, 0x00ffffff, sss);
                    else SendClientMessage(i, 0xFFB6C1ff, sss);
                }
            }
        }
    }
    if(AdminPlayer(playerid) == 0) SetPVarInt(playerid, "flood_global", gettime()+(60*2));
    if(ModoAdmin[playerid] == 0)
    {
        if(Inventario[playerid][radii][inv_Tipo] == 0) Inventario[playerid][radii][inv_Tipo] = 100;
        Inventario[playerid][radii][inv_Tipo] --;
        if(Inventario[playerid][radii][inv_Tipo] == 1)
        {
            Inventario[playerid][radii][inv_ID] = 0;
            Inventario[playerid][radii][inv_Tipo] = 0;
            Inventario[playerid][radii][inv_Unidades] = 0;
            if(invaberto[playerid] == 2) abririnv(playerid, 2);
            ms(playerid, 0, "Your radio communicator has reached its usage limit and has been discarded from your Inventory!");
        }
    }
    return 1;
}


CMD:settings(playerid, params[]) return cmd_config(playerid, params);
CMD:config(playerid, params[])
{
    mostrar_configuracoes(playerid);
    return 1;
}

CMD:discord(playerid, params[])
{
    ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_STYLE_MSGBOX, "Server Discord", "\n\n{ffffff}https://discord.gg/Qvf5NUtqMg\n\n\n", "Ok", "Back");
    return 1;
}

CMD:credits(playerid, params[])
{
    String_Gigante[0] = EOS;
    for(new i; i<sizeof(Creditos); i++) strcat(String_Gigante, Creditos[i]);
    ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_STYLE_MSGBOX, "Credits", String_Gigante, "Ok", "Back");
    return 1;
}



CMD:drop(playerid, params[])
{
    ShowPlayerDialog_(playerid, DIALOG_DROPAR, DIALOG_STYLE_LIST, "{ffff00}Drop Materials", "Wood\nMetal\nStone\nGunpowder\nMoney", "Continue", "Close");
    return 1;
}

CMD:editloot(playerid, params[])
{
    new loot;
    if(sscanf(params, "d", loot))
    {
        new tem;
        for(new i; i<MAX_LOOT; i++)
        {
            if(Loot[i][loot_Existe] == 0) continue;
            if(IsPlayerInRangeOfPoint(playerid, 2, Loot[i][loot_X], Loot[i][loot_Y], Loot[i][loot_Z]))
            {
                EditDynamicObject2(playerid, Loot[i][loot_Obj],  0);
                ms(playerid, 3, "Move the loot chest to the correct position and save the edit.");
                return 1;
            }
        }
        if(tem == 0) return ms(playerid, 2, "Usage: /editloot [loot ID] ( or use the command near a loot ).");
    }
    if(loot < 0 || loot >= MAX_LOOT) return ms(playerid, 2, "Invalid Loot ID!");
    if(Loot[loot][loot_Existe] == 0) return ms(playerid, 2, "This Loot ID does not exist!");
    EditDynamicObject2(playerid, Loot[loot][loot_Obj],  0);
    ms(playerid, 3, "Move the loot chest to the correct position and save the edit.");
    return 1;
}

CMD:destroyloot(playerid, params[])
{
    new loot;
    new sss[300];
    if(sscanf(params, "d", loot))
    {
        new tem;
        for(new i; i<MAX_LOOT; i++)
        {
            if(Loot[i][loot_Existe] == 0) continue;
            if(IsPlayerInRangeOfPoint(playerid, 2, Loot[i][loot_X], Loot[i][loot_Y], Loot[i][loot_Z]))
            {
                destruir_loot(i);
                format(sss, 300, "You destroyed Loot ID: %d.", i);
                ms(playerid, 3, sss);
                return 1;
            }
        }
        if(tem == 0) return ms(playerid, 2, "Usage: /destroyloot [loot ID] ( or use the command at a loot location ).");
    }
    if(loot < 0 || loot >= MAX_LOOT) return ms(playerid, 2, "Invalid Loot ID!");
    if(Loot[loot][loot_Existe] == 0) return ms(playerid, 2, "This Loot ID does not exist!");
    format(sss, 300, "You destroyed Loot ID: %d.", loot);
    ms(playerid, 3, sss);
    destruir_loot(loot);
    return 1;
}

CMD:criarloot(playerid, params[])
{
	new tip;
	if(sscanf(params, "d", tip)) return ms(playerid, 2, "Use: /criarloot [Classe ( 0, 1 ou 2 )].");
	if(tip != 0 && tip != 1 && tip != 2 ) return ms(playerid, 0, "Use uma Classe entre 0, 1 ou 2 !");
	new Float:pos[4];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);
	PegarFrente(pos[0], pos[1], pos[3], -2.0);
	PegarAltura(pos[0], pos[1], pos[2], 2);
    new cc = criar_loot(pos[0], pos[1], pos[2], pos[3], tip);
    if(cc == -1) return ms(playerid, 0, "Maximum number of Loots reached!");
	new sss[150];
	format(sss, 150, "Posicao de Loot ID: %d criada.", cc);
	ms(playerid, 3, sss);
	EditDynamicObject2(playerid, Loot[cc][loot_Obj],  0);
	ms(playerid, 3, "Move the loot chest to the correct position, and save the edit.");
	return 1;
}

CMD:trazerveiculo(playerid, params[])
{
	new i;
	if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /trazerveiculo [ID do Veiculo].");
	if(i < 0 || i >= MAX_VEHICLES) return ms(playerid, 0, "This vehicle does not exist!");
	if(GetVehicleModel(i) == 0) return ms(playerid, 0, "This vehicle does not exist!");
    format(string_prox, 300, " Admin %s pulled the vehicle ID: %d '%s' ",Nome(playerid), i, NomeVeiculos[GetVehicleModel(i)-400]);
	ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
	new Float:p[4];
	GetPlayerPos(playerid, p[0], p[1], p[2]);
	GetPlayerFacingAngle(playerid, p[3]);
	PegarFrente(p[0], p[1], p[3], -3);
	SetVehiclePos(i, p[0], p[1], p[2]);
	SetVehicleZAngle(i, p[3]+90.0);
	return 1;
}

CMD:nomeposto(playerid, params[])
{
    new i;
    new nome[40];
    new sss[150];
	if(sscanf(params, "ds[40]", i, nome)) return ms(playerid, 2, "Use: /renameposto [Posto ID] [ New Name ].");
	if(i < 0 || i >= MAX_POSTOS) return ms(playerid, 0, "Gas station ID is invalid.");
	if(Posto[i][posto_Existe] == 0) return ms(playerid, 0, "This station does not exist!.");
	format(Posto[i][posto_Nome], 40, nome);
	format(sss, 150, "You changed the station name ID: %d, to '%s'.", i, Posto[i][posto_Nome]);
	ms(playerid, 4, sss);
    atualizar_posto(i);
	salvar_posto(i);
	return 1;
}

CMD:criarposto(playerid, params[])
{
    new sss[150];
    new nome[40];
    if(sscanf(params, "s[40]", nome)) return ms(playerid, 2, "Use: /criarposto [Nome do Posto].");
    for(new i; i<MAX_POSTOS; i++)
    {
        if(Posto[i][posto_Existe] == 0)
        {
            Posto[i][posto_Existe] = 1;
	        Posto[i][posto_Litros] = 150;
	        format(Posto[i][posto_Nome], 40, nome);
	        GetPlayerPos(playerid, Posto[i][posto_X], Posto[i][posto_Y], Posto[i][posto_Z]);
            format(sss, 150, "You created the station '%s' ID: %d.", Posto[i][posto_Nome], i);
			ms(playerid, 4, sss);
			atualizar_posto(i);
			salvar_posto(i);
            return 1;
        }
	}
    ms(playerid, 0, "Maximum number of gas stations reached!");
	return 1;
}

CMD:destruirposto(playerid, params[])
{
    new i;
    new sss[150];
	if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /destruirposto [ID do Posto].");
	if(i < 0 || i >= MAX_POSTOS) return ms(playerid, 0, "Invalid Gas Station ID.");
	if(Posto[i][posto_Existe] == 0) return ms(playerid, 0, "This station does not exist!");
	format(sss, 150, "You destroyed the station '%s' ID: %d.", Posto[i][posto_Nome], i);
	ms(playerid, 4, sss);
	Posto[i][posto_Existe] = 0;
    atualizar_posto(i);
	salvar_posto(i);
	return 1;
}

CMD:abastecerposto(playerid, params[])
{
    new i;
    new sss[150];
	if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /abastecerposto [ID do Posto].");
	if(i < 0 || i >= MAX_POSTOS) return ms(playerid, 0, "Gas station ID is invalid.");
	if(Posto[i][posto_Existe] == 0) return ms(playerid, 0, "This station does not exist!.");
	format(sss, 150, "You refueled the station '%s' ID: %d.", Posto[i][posto_Nome], i);
	ms(playerid, 4, sss);
	Posto[i][posto_Litros] = 150;
	return 1;
}

CMD:trazerposto(playerid, params[])
{
    new i;
    new sss[150];
	if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /trazerposto [ID do Posto].");
	if(i < 0 || i >= MAX_POSTOS) return ms(playerid, 0, "Gas station ID is invalid.");
	if(Posto[i][posto_Existe] == 0) return ms(playerid, 0, "This station does not exist!.");
    GetPlayerPos(playerid, Posto[i][posto_X], Posto[i][posto_Y], Posto[i][posto_Z]);
	atualizar_posto(i);
	salvar_posto(i);
	format(sss, 150, "You changed the spawn position of the station '%s' ID: %d.", Posto[i][posto_Nome], i);
	ms(playerid, 4, sss);
	return 1;
}


CMD:irposto(playerid, params[])
{
    new i;
	if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /irposto [ID do Posto].");
	if(i < 0 || i >= MAX_POSTOS) return ms(playerid, 0, "Gas station ID is invalid.");
	if(Posto[i][posto_Existe] == 0) return ms(playerid, 0, "This station does not exist!.");
	format(string_prox, 300, " Admin %s went to Station ID: %d '%s' ", Nome(playerid), i, Posto[i][posto_Nome]);
	ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
	SetPlayerPos(playerid, Posto[i][posto_X], Posto[i][posto_Y], Posto[i][posto_Z]);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	return 1;
}

CMD:irveiculo(playerid, params[])
{
	new i;
	if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /irveiculo [ID do Veiculo].");
	if(i < 0 || i >= MAX_VEHICLES) return ms(playerid, 0, "This vehicle does not exist!");
	if(GetVehicleModel(i) == 0) return ms(playerid, 0, "This vehicle does not exist!");
    format(string_prox, 300, " Admin %s went to vehicle ID: %d '%s' ", Nome(playerid), i, NomeVeiculos[GetVehicleModel(i)-400]);
	ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
	new Float:p[4];
	GetVehiclePos(i, p[0], p[1], p[2]);
	GetVehicleZAngle(i, p[3]);
	PegarFrente(p[0], p[1], p[3], -2);
	SetPlayerPos(playerid, p[0], p[1], p[2]);
	return 1;
}

CMD:respawnserver(playerid, params[])
{
    new sss[150];
    RespawnTudo();
    respawn_auto = tempo_respawn;
	format(sss, 150, "Administrator %s has restarted the server!", Nome(playerid));
	for(new i; i<MAX_PLAYERS; i++) if(Online(i) && Modo[i] == 1) ms(i, 4, sss);
	return 1;
}

CMD:createcar(playerid, params[])
{
	new Float:p[4];
	GetPlayerPos(playerid, p[0], p[1], p[2]);
	GetPlayerFacingAngle(playerid, p[3]);
	new model, metais, sucata, polvora;
	if(sscanf(params, "dddd", model, metais, sucata, polvora)) return ms(playerid, 2, "Usage: /createcar [Model] [Metals] [Scrap] [Gunpowder].");
	if(model < 400 || model > 611) return ms(playerid, 0, "Use a model from 400 - 611!");
	if(metais <= 0) return ms(playerid, 0, "Use a Metals value greater than 0!");
	if(sucata <= 0) return ms(playerid, 0, "Use a Scrap value greater than 0!");
	if(polvora <= 0) return ms(playerid, 0, "Use a Gunpowder value greater than 0!");
	new c = criar_carro( model, metais, sucata, polvora, p[0], p[1], p[2], p[3]);
	if(c == -1) return ms(playerid, 0, "Maximum number of cars reached!");
	new sss[150];
	format(sss, 150, "Old car ID: %d created.", c);
	ms(playerid, 1, sss);
	salvar_carro(c);
	return 1;
}


CMD:destroycars(playerid, params[])
{
	for(new i; i<MAX_CARROS; i++)
	{
		if(Carros[i][fv_Existe] != 0)
		{
		    Carros[i][fv_Existe] = 0;
		    atualizar_carro(i);
			salvar_carro(i);
		}
		return 1;
	}
	ms(playerid, 4, "You destroyed all old iron cars on the server!");
	return 1;
}

CMD:destroycar(playerid, params[])
{
	new c;
    if(sscanf(params, "d", c)) return ms(playerid, 2, "Usage: /destroycar [Old car ID].");
	if(c < 0 || c >= MAX_CARROS) return ms(playerid, 0, "Invalid old car ID.");
	if(Carros[c][fv_Existe] == 0) return ms(playerid, 0, "Invalid old car ID.");
    Carros[c][fv_Existe] = 0;
    atualizar_carro(c);
	new sss[150];
	format(sss, 150, "Old car ID: %d destroyed successfully.", c);
	ms(playerid, 1, sss);
	salvar_carro(c);
	return 1;
}

CMD:gotocar(playerid, params[])
{
    new c;
    if(sscanf(params, "d", c)) return ms(playerid, 2, "Use: /gotocar [ID of old car].");
	if(c < 0 || c >= MAX_CARROS) return ms(playerid, 0, "Invalid old car ID.");
	if(Carros[c][fv_Existe] == 0) return ms(playerid, 0, "Invalid old car ID.");
    if(ModoAdmin[playerid] == 0)
    {
        Kick(playerid);
        return 1;
    }

    SetPVarInt(playerid, "AC_TP", 1);
	new sss[150], Float:p[3];
    if(GetVehicleModel(Carros[c][fv_Veiculo]) != 0)
    {
    	GetVehiclePos(Carros[c][fv_Veiculo], p[0], p[1], p[2]);
    	SetPlayerPos(playerid, p[0], p[1], p[2]+1);
    	SetPlayerInterior(playerid, 0);
    	SetPlayerVirtualWorld(playerid, 0);
    }
    else
    {
        SetPlayerPos(playerid, Carros[c][fv_X], Carros[c][fv_Y], Carros[c][fv_Z]);
        SetPlayerVirtualWorld(playerid, 0);
        SetPlayerInterior(playerid, 0);
    }
	format(sss, 150, "You went to Old car ID: %d, '%s'", c, NomeVeiculos[Carros[c][fv_ModeloCarro]-400]);
	ms(playerid, 1, sss);
	return 1;
}

CMD:modelocarro(playerid, params[])
{
    new c, cc;
    if(sscanf(params, "dd", c, cc)) return ms(playerid, 2, "Usage: /carmodel [Old car ID] [Model].");
	if(c < 0 || c >= MAX_CARROS) return ms(playerid, 0, "Invalid old car ID.");
	if(Carros[c][fv_Existe] == 0) return ms(playerid, 0, "Invalid old car ID.");
	if(cc < 400 || cc > 611) return ms(playerid, 0, "Invalid car model, use from 400 - 611.");
    Carros[c][fv_ModeloCarro] = cc;
	atualizar_carro(c);
    new sss[150];
	format(sss, 150, "Model of Old car ID: %d changed to %d '%s'.", c, cc, NomeVeiculos[cc-400]);
	ms(playerid, 1, sss);
	salvar_carro(c);
	return 1;
}

CMD:copycar(playerid, params[])
{
	new c;
    if(sscanf(params, "d", c)) return ms(playerid, 2, "Usage: /copycar [Old car ID].");
	if(c < 0 || c >= MAX_CARROS) return ms(playerid, 0, "Invalid old car ID.");
	if(Carros[c][fv_Existe] == 0) return ms(playerid, 0, "Invalid old car ID.");
    new Float:p[4];
	GetPlayerPos(playerid, p[0], p[1], p[2]);
	GetPlayerFacingAngle(playerid, p[3]);
	new cc = criar_carro(Carros[c][fv_ModeloCarro], Carros[c][fv_Metais_Precisa], Carros[c][fv_Sucata_Precisa], Carros[c][fv_Polvora_Precisa], p[0], p[1], p[2], p[3]);
	if(cc == -1) return ms(playerid, 0, "Maximum number of cars reached!");
	atualizar_carro(cc);
	new sss[150];
	format(sss, 150, "Old car ID: %d created.", cc);
	ms(playerid, 1, sss);
	salvar_carro(cc);
	return 1;
}


CMD:menu(playerid, params[])
{
    if(tv_player[playerid] != -1) return ms(playerid, 0, "You cannot do this in /tv Mode!");
	for(new i; i<MAX_OFICINAS; i++)
	{
	    if(Oficina[i][o_Existe] == 0) continue;
        if(IsPlayerInRangeOfPoint(playerid, 20, Oficina[i][o_X],Oficina[i][o_Y],Oficina[i][o_Z]))
        {
            if(IsPlayerInAnyVehicle(playerid))
            {
                if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ms(playerid, 0, "You are not the driver of this vehicle!");
                if(GetPlayerVehicleID(playerid) == RC[playerid])
                {
                    ms(playerid, 0, "You cannot do this with this vehicle!");
                    return 1;
                }

				mostrar_tunings(playerid);
				return 1;
			}
			else
			{
			    ms(playerid, 0, "You are not in a vehicle!");
			    return 1;
			}
	    }
    }
    ms(playerid, 0, "You are not in a workshop!");
	return 1;
}

CMD:moveroficina(playerid, params[])
{
	for(new i; i<MAX_OFICINAS; i++)
	{
	    if(Oficina[i][o_Existe] == 0) continue;
        if(IsPlayerInRangeOfPoint(playerid, 15, Oficina[i][o_X],Oficina[i][o_Y],Oficina[i][o_Z]))
        {
            EditDynamicObject2(playerid, Oficina[i][o_Obj][0],  12942);
            ms(playerid, 1, "Move the workshop to the location you want, and save the changes.");
            return 1;
        }
	}
	return 1;
}

CMD:criaroficina(playerid, params[])
{
	new sss[150];
	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	new i = criar_oficina(pos[0], pos[1], pos[2]);
	if(i == -1) return ms(playerid, 0, "Maximum number of workshops reached!");
	Streamer_Update(playerid);
	format(sss, 150, "Workshop ID: %d created. Set the coordinates and save to complete.", i);
	ms(playerid, 1, sss);
	EditDynamicObject2(playerid, Oficina[i][o_Obj][0],  12942);
	return 1;
}


CMD:destruiroficina(playerid, params[])
{
    new sss[150];
	new i;
	if(sscanf(params, "d", i)) return ms(playerid, 2, "Usage: /destroyworkshop [Workshop ID].");
	if(i < 0 || i >= MAX_OFICINAS) return ms(playerid, 0, "This workshop ID does not exist!");
	if(Oficina[i][o_Existe] == 0 ) return ms(playerid, 0, "This workshop ID does not exist!");
	format(sss, 150, "You destroyed Workshop ID: %d.", i);
	ms(playerid, 1, sss);
	destruir_oficina(i);
	return 1;
}



CMD:setarskin(playerid, params[])
{
	new skin, id;
	if(sscanf(params, "ud", id, skin)) return ms(playerid, 1, "Usage: /setskin [ID/Nick] [0 - 311]");
	if(!Online(id)) return ms(playerid, 0, "This player is not online!");
	if(skin < 0 || skin > 311) return ms(playerid, 0, "Use a skin from 0 - 311");
	if(Modo[id] != 1) return ms(playerid, 0, "This player is not in Story mode!");
  	SetarSkin(id, skin);
	new sss[150];
	format(sss, 150, "You set the Skin of '%s' to ID: %d", Nome(id), skin);
	ms(playerid, 4, sss);
	format(sss, 150, "The Administrator '%s' set your Skin to ID: %d", Nome(playerid), skin);
	ms(id, 2, sss);
	return 1;
}

CMD:setlevel(playerid, params[])
{
    new level, id;
    if(sscanf(params, "ud", id, level)) return ms(playerid, 1, "Usage: /setlevel [ID/Nick] [level]");
    if(!Online(id)) return ms(playerid, 0, "This player is not online!");
    if(level < 0) return ms(playerid, 0, "Use a level greater than or equal to 0!");
    if(Modo[id] != 1) return ms(playerid, 0, "This player is not in Story mode!");
    pInfo[id][pLevel] = level;
    SetPlayerScore(id, level);
    new msg[150];
    format(msg, 150, "You have set the level of '%s' to: %d", Nome(id), level);
    ms(playerid, 4, msg);
    format(msg, 150, "Administrator '%s' has set your level to: %d", Nome(playerid), level);
    ms(id, 2, msg);
    return 1;
}

CMD:setbaselevel(playerid, params[])
{
    new level, id;
    if(sscanf(params, "dd", id, level)) return ms(playerid, 1, "Usage: /setbaselevel [Base ID] [level]");
    if(id < 0 || id >= MAX_BASES) return ms(playerid, 0, "This base does not exist!");
    if(Base[id][base_Existe] == 0) return ms(playerid, 0, "This base does not exist!");
    if(level < 0) return ms(playerid, 0, "Use a level greater than or equal to 0!");
    Base[id][base_Level] = level;
    new msg[150];
    format(msg, 150, "You have set the level of base '%s' to: %d", Base[id][base_Nome], level);
    ms(playerid, 4, msg);
    salvar_base(id);
    return 1;
}

CMD:idzombie(playerid, params[])
{
    new Float:pos[3];
    new msg[150];
    for(new i = 0; i < MAX_ZOMBIES; i++)
    {
        if(Zombie[i][z_Existe] == 1 && Zombie[i][z_Spawn] == 1)
        {
            FCNPC_GetPosition(Zombie[i][z_Zombie], pos[0], pos[1], pos[2]);
            if(IsPlayerInRangeOfPoint(playerid, 5, pos[0], pos[1], pos[2]))
            {
                format(msg, 150, "This Zombie ID is: %d.", i);
                ms(playerid, 4, msg);
                return 1;
            }
        }
    }
    ms(playerid, 0, "You are not close to a Zombie!");
    return 1;
}

CMD:destroyzombie(playerid, params[])
{
    new i;
    if(sscanf(params, "d", i)) return ms(playerid, 2, "Usage: /destroyzombie [id].");
    if(i < 0 || i >= MAX_ZOMBIES) return ms(playerid, 0, "Invalid Zombie ID!");
    if(Zombie[i][z_Existe] == 0) return ms(playerid, 0, "This Zombie does not exist!");
    
    Zombie[i][z_Spawn] = 0;
    Zombie[i][z_Existe] = 0;
    Zombie[i][z_Alvo] = -1;
    Zombie[i][z_Vida] = 0;
    Zombie[i][z_X] = 0;
    Zombie[i][z_Y] = 0;
    Zombie[i][z_Z] = 0;
    Zombie[i][z_A] = 0;
    Zombie[i][z_Skin] = 0;
    Zombie[i][z_Colete] = 0;
    Zombie[i][z_Capacete] = 0;
    Zombie[i][z_Mascara] = 0;
    Zombie[i][z_Arma] = 0;
    Zombie[i][z_Municao] = 0;
    KillTimer_(Zombie[i][z_Timer]);
    if(Zombie[i][z_Zombie] != INVALID_PLAYER_ID) FCNPC_Destroy(Zombie[i][z_Zombie]);

    new msg[150];
    format(msg, 150, "You have destroyed Zombie ID: %d.", i);
    ms(playerid, 4, msg);
    salvar_zombie(i);
    return 1;
}

CMD:createzombie(playerid, params[])
{
    dialog_zombie(playerid);
    return 1;
}

CMD:createzombie123456(playerid, params[])
{
    new skin;
    new Float:pos[4];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    GetPlayerFacingAngle(playerid, pos[3]);
    if(sscanf(params, "d", skin)) return ms(playerid, 2, "Use: /createzombie [ Type ]");
    if(skin < 1 || skin >= sizeof Info_Zombies) return ms(playerid, 2, "Invalid Zombie Type!");
    
    new c = criar_zombie(pos[0], pos[1], pos[2], pos[3], skin);
    if(c == -1) return ms(playerid, 0, "Maximum number of Zombies has been reached!");
    
    ms(playerid, 4, "Zombie has been created.");
    salvar_zombie(c);
    return 1;
}

CMD:setbasexp(playerid, params[])
{
    new xp, id;
    if(sscanf(params, "dd", id, xp)) return ms(playerid, 1, "Usage: /setbasexp [Base ID] [XP]");
    if(id < 0 || id >= MAX_BASES) return ms(playerid, 0, "This base does not exist!");
    if(Base[id][base_Existe] == 0) return ms(playerid, 0, "This base does not exist!");
    if(xp < 0) return ms(playerid, 0, "Use XP greater than or equal to 0!");
    Base[id][base_XP] = xp;
    new msg[150];
    format(msg, 150, "You have set the XP of base '%s' to: %d", Base[id][base_Nome], xp);
    ms(playerid, 4, msg);
    salvar_base(id);
    return 1;
}

CMD:setxp(playerid, params[])
{
    new xp, id;
    if(sscanf(params, "ud", id, xp)) return ms(playerid, 1, "Usage: /setxp [ID/Nick] [XP]");
    if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
    if(xp < 0) return ms(playerid, 0, "Use XP greater than or equal to 0!");
    if(Modo[id] != 1) return ms(playerid, 0, "This player is not in Story mode!");
    pInfo[id][pXPH] = xp;
    new msg[150];
    format(msg, 150, "You have set the XP of '%s' to: %d", Nome(id), xp);
    ms(playerid, 4, msg);
    format(msg, 150, "Administrator '%s' has set your XP to: %d", Nome(playerid), xp);
    ms(id, 2, msg);
    return 1;
}

CMD:basehelp(playerid, params[])
{
    new msg[1000];
    strcat(msg, "{ffffff}/destroybase {a1a1a1}Destroys an existing base.\n");
    strcat(msg, "{ffffff}/basename {a1a1a1}Changes the name of an existing base.\n");
    strcat(msg, "{ffffff}/bringbase {a1a1a1}Saves the base spawn location to a new position.\n");
    strcat(msg, "{ffffff}/baseowner {a1a1a1}Changes the base owner.\n");
    strcat(msg, "{ffffff}/gobase {a1a1a1}Go to an existing base.\n");
    strcat(msg, "{ffffff}/bringtable {a1a1a1}Brings the Craft Table of the base to your position.\n");
    strcat(msg, "{ffffff}/bringchest {a1a1a1}Brings the Material Chest of the base to your position.\n");
    strcat(msg, "{ffffff}/bringrecycler {a1a1a1}Brings the Recycling Machine of the base to your position.\n");
    ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_STYLE_MSGBOX, "Commands for Editing Base", msg, "Ok", "Close");
    return 1;
}

CMD:gobase(playerid, params[])
{
    new b;
    if(sscanf(params, "d", b)) return ms(playerid, 0, "Usage: /gobase [base id].");
    if(b < 0 || b >= MAX_BASES) return ms(playerid, 0, "Invalid base ID!");
    if(Base[b][base_Existe] == 0) return ms(playerid, 0, "This base does not exist!");
    
    SetPlayerPos(playerid, Base[b][base_X], Base[b][base_Y], Base[b][base_Z]);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    return 1;
}


CMD:donobase(playerid, params[])
{
    new b, id;
    if(sscanf(params, "du", b, id)) return ms(playerid, 0, "Usage: /setbaseowner [base id] [ID/Nick].");
    if( b < 0 || b >= MAX_BASES ) return ms(playerid, 0, "Invalid base ID!");
	if(Base[b][base_Existe] == 0) return ms(playerid, 0, "This base does not exist!");
	if(!Online(id)) return ms(playerid, 0, "This player is not online!");

	new basi = BasePlayer(id);
	if(basi != -1)
	{
	    for(new ii; ii<MAX_MEMBROS; ii++)
		{
	        if(Comparar(Membro[basi][ii], Nome(id)))
		    {
	            format(Membro[basi][ii], MAX_PLAYER_NAME, Nome(-1));
	        }
	    }
	    salvar_base(basi);
	}
	format(Membro[b][0], MAX_PLAYER_NAME, Nome(id));
	for(new ca; ca<MAX_CAMERAS; ca++)
	{
	    if(Camera[ca][ca_Existe] == 0) continue;
	    if(Comparar(Nome(id), Camera[ca][ca_Dono]))
	    {
	        Camera[ca][ca_Base] = b;
	        salvar_camera(ca);
	    }
	}

    new sss[150];
	format(sss, 150, "You have set %s as the new owner of the base: %s [%d]", Nome(id), Base[b][base_Nome], b);
    ms(playerid, 4, sss);
    atualizar_base(b, 1);
    salvar_base(b);
    base_player[id] = b;
	return 1;
}

CMD:trazerbase(playerid, params[])
{
    new b;
    if(sscanf(params, "d", b)) return ms(playerid, 0, "Usage: /bringbase [id].");
    if( b < 0 || b >= MAX_BASES ) return ms(playerid, 0, "Invalid base ID!");
	if(Base[b][base_Existe] == 0) return ms(playerid, 0, "This base does not exist!");
	GetPlayerPos(playerid, Base[b][base_X], Base[b][base_Y], Base[b][base_Z]);
    new sss[150];
	format(sss, 150, "You have changed the spawn location of the base: %s [%d]", Base[b][base_Nome], b);
    ms(playerid, 4, sss);
    atualizar_base(b);
	return 1;
}

CMD:nomebase(playerid, params[])
{
    new b, nome[40];
    if(sscanf(params, "ds[40]", b, nome)) return ms(playerid, 0, "Usage: /basename [id] [New Name].");
    if( b < 0 || b >= MAX_BASES ) return ms(playerid, 0, "Invalid base ID!");
	if(Base[b][base_Existe] == 0) return ms(playerid, 0, "This base does not exist!");
	format(Base[b][base_Nome], 40, nome);
    new sss[150];
	format(sss, 150, "Admin %s changed the base name: %s [%d], to: %s", Nome(playerid), Base[b][base_Nome], b, nome);
    for(new i; i<MAX_PLAYERS; i++) if(Online(i) && Modo[i] == 1) ms(i, 4, sss);
    atualizar_base(b, 1);
    salvar_base(b);
	return 1;
}

CMD:destruirbase(playerid, params[])
{
	new b, Motivo[40];
	if(sscanf(params, "ds[40]", b, Motivo)) return ms(playerid, 0, "Usage: /destroybase [id] [Reason].");
	if( b < 0 || b >= MAX_BASES ) return ms(playerid, 0, "Invalid base ID!");
	if(Base[b][base_Existe] == 0) return ms(playerid, 0, "This base does not exist!");
    new sss[150];
	format(sss, 150, "Admin %s destroyed Base: %s [%d], for reason: %s", Nome(playerid), Base[b][base_Nome], b, Motivo);
    for(new i; i<MAX_PLAYERS; i++) if(Online(i) && Modo[i] == 1) ms(i, 4, sss);
    destruir_base(b);
	return 1;
}


// CMD:adminduty(playerid, params[])
// {
// 	if(AdminPlayer(playerid) == 0) return ms(playerid, 0, "Anda bukan admin!");
// 	if(gps_player[playerid] == 0)
//     {
//         if(player_gps[playerid] > 0)
//         {
//             GZ_EsconderGzPlayer(playerid, GZ_PRETA);
//             gps_player[playerid] = 1;
//             format(string_prox, 300, " Player %s turned on their GPS ", Nome(playerid));
//             ProxDetector(15.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
//             GameTextForPlayer(playerid, "~g~~h~~h~GPS ON", 1500, 3);
//         }
//         else ms(playerid, 0, "The GPS does not have enough battery, please try again later!");
//     }
// 	else
//     {
//         gps_player[playerid] = 0;
//         GZ_MostrarGzPlayer(playerid, GZ_PRETA);
//         format(string_prox, 300, " Player %s turned off their GPS ", Nome(playerid));
//         ProxDetector(15.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
//         GameTextForPlayer(playerid, "~R~GPS OFF", 1500, 3);
//     }

// 	if(Modo[playerid] != 1) return ms(playerid, 0, "Kamu harus berada di Mode Dayz untuk melakukan ini !");
// 	if(GetPVarInt(playerid, "flood_adm") > gettime()) return ms(playerid, 0, "Kamu nggak bisa pake perintah ini terlalu sering !");
// 	new sss[150];
// 	if(ModoAdmin[playerid] == 0)
// 	{
// 	    ModoAdmin[playerid] = 1;
// 	    format(sss, 150, "Administrator %s sekarang lagi di mode Duty.", Nome(playerid));
// 	    SetPVarInt(playerid, "flood_adm", gettime()+3);
// 	    for(new pla; pla<MAX_PLAYERS; pla++)
// 		{
// 		    if(Online(pla))
// 		    {
// 		        if(hackeando_id[pla] == playerid)
// 		        {
// 		            hackeando_id[pla] = -1;
// 				    hackeando_tempo[pla] = 0;
// 					ms(pla, 3, "Admin yang tadi nge-hack sekarang masuk mode Kerja, lokasi hilang !");
// 		        }
// 			}
// 		}
// 	}
// 	else
// 	{
// 	    ModoAdmin[playerid] = 0;
// 	    format(sss, 150, "Administrator %s sekarang masuk ke mode Game.", Nome(playerid));
// 	    SetPVarInt(playerid, "flood_adm", gettime()+3);
// 	}
// 	for(new i; i<MAX_PLAYERS; i++) if(Online(i) && Modo[i] == 1) ms(i, 4, sss);
// 	return 1;
// }


CMD:adminduty(playerid, params[])
{
	if(!Online(playerid)) return 0;
	if(Logado[playerid] != 1) 
    {
        printf("[SECURITY] Player %s (ID: %d) attempted /adminduty without login!", Nome(playerid), playerid);
        return ms(playerid, 0, "You must be logged in first!");
    }
	if(AdminPlayer(playerid) < 1) 
    {
        printf("[SECURITY] Non-admin Player %s (ID: %d) attempted /adminduty!", Nome(playerid), playerid);
        return ms(playerid, 0, "Anda bukan admin!");
    }
	if(Modo[playerid] != 1) return ms(playerid, 0, "You must be in DayZ Mode to do this!");
	if(GetPVarInt(playerid, "flood_adm") > gettime()) return ms(playerid, 0, "You cannot use this command too frequently!");
	if(gps_player[playerid] == 0)
    {
        if(player_gps[playerid] > 0)
        {
            GZ_EsconderGzPlayer(playerid, GZ_PRETA);
            gps_player[playerid] = 1;
            format(string_prox, 300, " Player %s turned on their GPS ", Nome(playerid));
            ProxDetector(15.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
            GameTextForPlayer(playerid, "~g~~h~~h~GPS ON", 1500, 3);
        }
        else ms(playerid, 0, "The GPS does not have enough battery, please try again later!");
    }
	else
    {
        gps_player[playerid] = 0;
        GZ_MostrarGzPlayer(playerid, GZ_PRETA);
        format(string_prox, 300, " Player %s turned off their GPS ", Nome(playerid));
        ProxDetector(15.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
        GameTextForPlayer(playerid, "~R~GPS OFF", 1500, 3);
    }
	new sss[150];
	if(ModoAdmin[playerid] == 0)
	{
	    ModoAdmin[playerid] = 1;
	    format(sss, 150, "Administrator %s sekarang lagi di mode Duty.", Nome(playerid));
	    SetPVarInt(playerid, "flood_adm", gettime()+3);
	    for(new pla; pla<MAX_PLAYERS; pla++)
		{
		    if(Online(pla))
		    {
		        if(hackeando_id[pla] == playerid)
		        {
		            hackeando_id[pla] = -1;
				    hackeando_tempo[pla] = 0;
					ms(pla, 3, "Admin yang tadi nge-hack sekarang masuk mode Kerja, lokasi hilang !");
		        }
			}
		}
	}
	else
	{
	    ModoAdmin[playerid] = 0;
	    format(sss, 150, "Administrator %s sekarang masuk ke mode Game.", Nome(playerid));
	    SetPVarInt(playerid, "flood_adm", gettime()+3);
	}
	for(new i; i<MAX_PLAYERS; i++) if(Online(i) && Modo[i] == 1) ms(i, 4, sss);
	return 1;
}

CMD:trabalho2(playerid, params[])
{
	if(GetPVarInt(playerid, "flood_adm") > gettime()) return ms(playerid, 0, "You cannot use this command too frequently!");
	if(ModoAdmin[playerid] == 0)
	{
	    ModoAdmin[playerid] = 1;
	    ms(playerid, 4, "You entered work mode without anyone knowing!");
	    SetPVarInt(playerid, "flood_adm", gettime()+3);
	    for(new pla; pla<MAX_PLAYERS; pla++)
		{
		    if(Online(pla))
		    {
		        if(hackeando_id[pla] == playerid)
		        {
		            hackeando_id[pla] = -1;
				    hackeando_tempo[pla] = 0;
					ms(pla, 3, "The Admin who was hacking entered Work Mode, location lost!");
		        }
			}
		}
	}
	else
	{
	    ModoAdmin[playerid] = 0;
	    ms(playerid, 4, "You exited work mode without anyone knowing!");
	    SetPVarInt(playerid, "flood_adm", gettime()+3);
	}
	return 1;
}

CMD:gmx2(playerid, params[])
{
    GMX = 1;
    SendRconCommand("gmx");
	return 1;
}

CMD:gmx(playerid, params[])
{
    new sss[150];
	if(GMX == 1) return ms(playerid, 0, "The server is already restarting!");
	gmx();
	format(sss, 150, "[GMX] Administrator %s is restarting the server.", Nome(playerid));
	escrever_log_gmx(sss);
    for(new i; i<MAX_PLAYERS; i++) if(Online(i)) ms(i, 4, sss);
	return 1;
}

CMD:desbanir(playerid, params[])
{
	new conta[MAX_PLAYER_NAME], Motivo[40];
	if(sscanf(params, "s[24]s[40]", conta, Motivo)) return ms(playerid, 0, "Use: /desbanir [ Nick ] [ Motivo ]");
	new file[80];
	new file2[80];
    format(file, 80, "Banidos/%s.txt", conta);
    new sss[150];
    new sim;
    if(DOF2_FileExists(file))
    {
        format(file2, 80, "IPs_Banidos/%s.txt", DOF2_GetString(file, "ip"));
        if(DOF2_FileExists(file2)) DOF2_RemoveFile(file2);
        sim = 1;
        DOF2_RemoveFile(file);
    }
    format(file, 80, "Ban_Agendados/%s.txt", conta);
    if(DOF2_FileExists(file))
    {
        format(file2, 80, "IPs_Banidos/%s.txt", DOF2_GetString(file, "ip"));
        if(DOF2_FileExists(file2)) DOF2_RemoveFile(file2);
        sim = 1;
        DOF2_RemoveFile(file);
    }
    format(sss, 150, "Account '%s' is not banned!", conta);
    if(sim == 0) return ms(playerid, 0, sss);
    format(sss, 150, "[UNBAN] Administrator %s has unbanned '%s' reason: %s", Nome(playerid), conta, Motivo);
    for(new i; i<MAX_PLAYERS; i++) if(Online(i)) ms(i, 4, sss);
    escrever_log_ban(sss);
	return 1;
}

CMD:mudarsenha(playerid, params[])
{
    new id[MAX_PLAYER_NAME], novasenha[40];
    new sss[300];
    if(sscanf(params, "s[24]s[40]", id, novasenha)) return ms(playerid, 0, "Use: /mudarsenha [ Nick ] [ nova senha ]");
	if(strlen(novasenha) < 4 || strlen(novasenha) > 12) return ms(playerid, 0, "A senha deve conter de 4 a 12 caracteres !");

    new file[80];
	format(file, 80, "Whitelist/%s.txt", id);
	if(DOF2_FileExists(file))
	{
	    DOF2_SetString(file, "senha", novasenha);
	    DOF2_SaveFile();
	    format(sss, 300, "You have changed the password of '%s' to [ %s ].", id, novasenha);
	    ms(playerid, 1, sss);
	    if(IsPlayerOnline(id))
		{
		    new i = GetPlayerID(id);
		    if(Online(i))
		    {
		        format(sss, 150, "Admin '%s' has changed your password to [ %s ]", Nome(playerid), novasenha);
		        ms(i, 2, sss);
		        return 1;
		    }
		}
		return 1;
	}
	ms(playerid, 0, "This account does not exist!");
	return 1;
}

CMD:puniroff(playerid, params[])
{
    new id[MAX_PLAYER_NAME], tempo, Motivo[150];
    new sss[300];
    if(sscanf(params, "s[24]ds[150]", id, tempo, Motivo)) return ms(playerid, 0, "Use: /punirnick [ Nick ] [ Minutos ] [ Motivo ]");
	if(tempo < 0) return ms(playerid, 0, "Use um tempo maior ou igual a 0 minutos !");
	if(IsPlayerOnline(id))
	{
	    new i = GetPlayerID(id);
	    if(Online(i))
	    {
	        format(sss, 150, "%d %d %s", i, tempo, Motivo);
	        cmd_punir(playerid, sss);
	        return 1;
	    }
	}

	new file[80];
	format(file, 80, "Whitelist/%s.txt", id);
	if(DOF2_FileExists(file))
	{
	    new number = DOF2_GetInt(file, "pCadeia");
	    if(tempo == 0) number = 0;
	    else number += tempo*60;

	    DOF2_SetInt(file, "pCadeia", number);
	    DOF2_SetString(file, "pCadeiaAdmin", Nome(playerid));
	    DOF2_SetString(file, "pCadeiaMotivo", Motivo);
	    DOF2_SaveFile();
	    format(sss, 300, "[PUNICAO] %s puniu %s por %d Minutos: %s.",Nome(playerid), id, tempo, Motivo);
	    escrever_log_punicao(sss);
		for(new i; i<MAX_PLAYERS; i++) if(Online(i)) ms(i, 4, sss);
		return 1;
	}
	ms(playerid, 0, "This account does not exist!");
	return 1;
}

CMD:punir(playerid, params[])
{
	new id, tempo, Motivo[150];
	if(sscanf(params, "uds[150]", id, tempo, Motivo)) return ms(playerid, 0, "Use: /punir [ ID/Nick ] [ Minutos ] [ Motivo ]");
	if(!Online(id)) return ms(playerid, 0, "This player is not online, use /puniroff.");
    new sss[300];
    if(tempo < 0) return ms(playerid, 0, "Use um tempo maior ou igual a 0 minutos !");
    format(sss, 300, "[PUNICAO] %s puniu %s por %d Minutos: %s.",Nome(playerid), Nome(id), tempo, Motivo);
    escrever_log_punicao(sss);

    new number = pInfo[id][pCadeia];
    if(tempo == 0) number = 0;
    else number += tempo*60;


	for(new i; i<MAX_PLAYERS; i++) if(Online(i)) ms(i, 4, sss);
	pInfo[id][pCadeia] = number;
	format(pInfo[id][pCadeiaMotivo], 150, Motivo);
	format(pInfo[id][pCadeiaAdmin], MAX_PLAYER_NAME, Nome(playerid));
	salvarplayer(id);
	if(SalaPlayer[id] != -1)
	{
     	kikar(id);
	}
	else
	{
		Modo[id] = 0;
		SpawnPlayer(id);
	}
	return 1;
}


CMD:kikar(playerid, params[])
{
	new id, Motivo[40];
	if(sscanf(params, "us[40]", id, Motivo)) return ms(playerid, 0, "Use: /kikar [ ID/Nick ] [ Motivo ]");
	if(IsPlayerNPC(id)) return ms(playerid, 0, "You cannot kick an NPC.");
    if(!IsPlayerConnected(id)) return ms(playerid, 0, "This player is not connected.");
    new sss[300];
    format(sss, 300, "[Kick] Admin %s kicked %s reason: %s.", Nome(playerid), Nome(id), Motivo);
    escrever_log_kick(sss);
	for(new i; i<MAX_PLAYERS; i++) if(Online(i)) ms(i, 4, sss);
	kikar(id);
	return 1;
}

CMD:agendarban(playerid, params[])
{
	new sss[300];
	new conta[MAX_PLAYER_NAME];
	new dias;
	new file[80];
	new file2[80];
	new file3[80];
	new Motivo[40];

	if(sscanf(params, "s[24]ds[40]", conta, dias, Motivo)) return ms(playerid, 0, "Use: /agendarban [ Nick ] [ Dias ] [ Motivo ]");
	format(file2, 80, "Whitelist/%s.txt", conta);
	if(!DOF2_FileExists(file2)) return ms(playerid, 0, "This account does not exist!");
	if(dias < 1) return ms(playerid, 0, "Use dias maior que 0 !");
    if(dias > 999) dias = 999;

	if(IsPlayerOnline(conta))
	{
	    new id = GetPlayerID(conta);
	    if(Online(id))
	    {
	        format(sss, 300, "%d %d %s", id, dias, Motivo);
	        cmd_banir(playerid, sss);
	        return 1;
	    }
	}

	new dd, mm, aa, hh, minss, seg;
	format(file, 80, "Banidos/%s.txt", conta);
    if(DOF2_FileExists(file))
    {
		new dias2 = dias+DOF2_GetInt(file, "ban_dias");
        DOF2_SetInt(file, "ban_dias", dias2);
        dd = DOF2_GetInt(file, "desban_dia");
        mm = DOF2_GetInt(file, "desban_mes");
        aa = DOF2_GetInt(file, "desban_ano");
        for(new i; i<dias; i++)
		{
		    dd++;
		    if(dd > dias_mes(mm))
		    {
		        dd-=dias_mes(mm);
		        mm++;
		        if(mm > 12)
		        {
		            mm-=12;
					aa++;
		        }
		    }
		}
		DOF2_SetInt(file, "desban_dia", dd);
		DOF2_SetInt(file, "desban_mes", mm);
		DOF2_SetInt(file, "desban_ano", aa);
		DOF2_SetString(file, "admin", Nome(playerid));
		DOF2_SetString(file, "motivo", Motivo);
		DOF2_SaveFile();
		format(sss, 150, "[BAN] Admin %s banned %s for +%d Days reason: %s.", Nome(playerid), conta, dias, Motivo);
    	for(new i; i<MAX_PLAYERS; i++) if(Online(i)) ms(i, 4, sss);
    	escrever_log_ban(sss);
        return 1;
    }

    format(file, 80, "Ban_Agendados/%s.txt", conta);
    if(DOF2_FileExists(file))
    {
        new dias2 = dias+DOF2_GetInt(file, "ban_dias");
        DOF2_SetInt(file, "ban_dias", dias2);
        dd = DOF2_GetInt(file, "desban_dia");
        mm = DOF2_GetInt(file, "desban_mes");
        aa = DOF2_GetInt(file, "desban_ano");
        for(new i; i<dias; i++)
		{
		    dd++;
		    if(dd > dias_mes(mm))
		    {
		        dd-=dias_mes(mm);
		        mm++;
		        if(mm > 12)
		        {
		            mm-=12;
					aa++;
		        }
		    }
		}
		DOF2_SetInt(file, "desban_dia", dd);
		DOF2_SetInt(file, "desban_mes", mm);
		DOF2_SetInt(file, "desban_ano", aa);
		DOF2_SetString(file, "admin", Nome(playerid));
		DOF2_SetString(file, "motivo", Motivo);
		DOF2_SaveFile();
		format(sss, 150, "[BAN] Admin %s scheduled ban for %s for +%d Days reason: %s.", Nome(playerid), conta, dias, Motivo);
    	for(new i; i<MAX_PLAYERS; i++) if(Online(i)) ms(i, 4, sss);
    	escrever_log_ban(sss);
		return 1;
	}
	else
	{
	    getdate(aa, mm, dd);
		gettime(hh, minss, seg);
		DOF2_CreateFile(file);
        DOF2_SetInt(file, "ban_dias", dias);
		DOF2_SetInt(file, "ban_dia", dd);
		DOF2_SetInt(file, "ban_mes", mm);
		DOF2_SetInt(file, "ban_ano", aa);
		DOF2_SetInt(file, "ban_hora", hh);
		DOF2_SetInt(file, "ban_minuto", minss);
		DOF2_SetInt(file, "ban_segundo", seg);
		DOF2_SetString(file, "ip", DOF2_GetString(file2, "pIP"));

		for(new i; i<dias; i++)
		{
		    dd++;
		    if(dd > dias_mes(mm))
		    {
		        dd-=dias_mes(mm);
		        mm++;
		        if(mm > 12)
		        {
		            mm-=12;
					aa++;
		        }
		    }
		}

		DOF2_SetInt(file, "desban_dia", dd);
		DOF2_SetInt(file, "desban_mes", mm);
		DOF2_SetInt(file, "desban_ano", aa);
		DOF2_SetString(file, "admin", Nome(playerid));
		DOF2_SetString(file, "motivo", Motivo);
		DOF2_SaveFile();
		format(sss, 150, "[BAN] Admin %s scheduled ban for %s for '%d' Days reason: %s.", Nome(playerid), conta, dias, Motivo);
    	for(new i; i<MAX_PLAYERS; i++) if(Online(i)) ms(i, 4, sss);

    	format(file3, 80, "IPs_Banidos/%s.txt", DOF2_GetString(file2, "pIP"));
    	if(!DOF2_FileExists(file3))
    	{
    	    DOF2_CreateFile(file3);
    	    DOF2_SaveFile();
    	}

    	escrever_log_ban(sss);
	}
	return 1;
}

CMD:banir(playerid, params[])
{
	if(AdminPlayer(playerid) == 0) return ms(playerid, 0, "You are not an admin!");
    new id, dias, Motivo[40];
	if(sscanf(params, "uds[40]", id, dias, Motivo)) return ms(playerid, 0, "Use: /ban [ ID/Nick ] [ Days ] [ Reason ]");
	if(!Online(id)) return ms(playerid, 0, "This player is not Online.");
	if(dias < 1) return ms(playerid, 0, "You have to ban for 1 day or more, use a value greater than 0.");
	if(dias > 999) dias = 999;
	new file[80];
	format(file, 80, "Banidos/%s.txt", Nome(id));
	if(!DOF2_FileExists(file)) DOF2_CreateFile(file);
	new dd, mm, aa, hh, minss, seg;
	getdate(aa, mm, dd);
	gettime(hh, minss, seg);

	DOF2_SetString(file, "ip", pInfo[id][pIP]);
	DOF2_SetInt(file, "ban_dias", dias);
	DOF2_SetInt(file, "ban_dia", dd);
	DOF2_SetInt(file, "ban_mes", mm);
	DOF2_SetInt(file, "ban_ano", aa);
	DOF2_SetInt(file, "ban_hora", hh);
	DOF2_SetInt(file, "ban_minuto", minss);
	DOF2_SetInt(file, "ban_segundo", seg);

	for(new i; i<dias; i++)
	{
	    dd++;
	    if(dd > dias_mes(mm))
	    {
	        dd-=dias_mes(mm);
	        mm++;
	        if(mm > 12)
	        {
	            mm-=12;
				aa++;
	        }
	    }
	}

	DOF2_SetInt(file, "desban_dia", dd);
	DOF2_SetInt(file, "desban_mes", mm);
	DOF2_SetInt(file, "desban_ano", aa);
	DOF2_SetString(file, "admin", Nome(playerid));
	DOF2_SetString(file, "motivo", Motivo);
	DOF2_SaveFile();

	new sss[150];
	format(sss, 150, "[BAN] Admin %s Banned %s for '%d' Days reason: %s.", Nome(playerid), Nome(id), dias, Motivo);
    for(new i; i<MAX_PLAYERS; i++) if(Online(i)) ms(i, 4, sss);

	format(file, 80, "IPs_Banidos/%s.txt", pInfo[id][pIP]);
	if(!DOF2_FileExists(file)) DOF2_CreateFile(file);

	banir(id);
	escrever_log_ban(sss);
	return 1;
}

CMD:goto(playerid, params[])
{
    if(AdminPlayer(playerid) == 0)
        return ms(playerid, 0, "You are not an admin!");
    
    new sss[300], id;

    if(Modo[playerid] != 1)
        return ms(playerid, 0, "You need to be in Story mode to do this!");

    if(sscanf(params, "u", id))
        return ms(playerid, 0, "Usage: /goto [ID/Nick]");

    if(!Online(id))
        return ms(playerid, 0, "This player is not online.");

    if(tv_player[id] != -1)
        return ms(playerid, 0, "This player is currently spectating someone with /tv!");

    if(Modo[id] != 1)
        return ms(playerid, 0, "This player needs to be in Story mode to do this!");

    if(olhando_camera[playerid] != -1)
        return ms(playerid, 0, "You are currently watching a camera!");

    if(olhando_camera[id] != -1)
        return ms(playerid, 0, "This player is currently watching a camera!");

    format(string_prox, 300, " Admin %s went to %s ", Nome(playerid), Nome(id));
    ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA, 0xBCA9F5AA, 0xBCA9F5AA, 0xBCA9F5AA, 0xBCA9F5AA);

    LevarPlayer(playerid, id);

    format(sss, 300, "Admin %s has come to you.", Nome(playerid));
    ms(id, 4, sss);

    return 1;
}

CMD:gotopos(playerid, params[])
{
    if(AdminPlayer(playerid) == 0) return ms(playerid, 0, "Anda bukan admin!");
    
    new Float:x, Float:y, Float:z, vw, interior;
    if(sscanf(params, "fffdd", x, y, z, vw, interior)) 
    {
        ms(playerid, 2, "PENGGUNAAN: /gotopos [x] [y] [z] [virtualworld] [interior]");
        return 1;
    }

    // Save current position for logging
    new Float:oldX, Float:oldY, Float:oldZ;
    GetPlayerPos(playerid, oldX, oldY, oldZ);
    
    // Disable anti-cheat temporarily for admin
    SetPVarInt(playerid, "ignorar_gelo", 1);
    SetPVarInt(playerid, "emcombate", gettime()+10);
    invuneravel[playerid] = gettime()+3;
    
    // Freeze player during teleport
    TogglePlayerControllable(playerid, 0);
    
    // Set position with delay to avoid detection
    SetTimerEx("AdminGotoPos", 500, false, "dfffdd", playerid, x, y, z, vw, interior);
    
    // Log admin action
    new str[150];
    format(str, sizeof(str), "[ADMIN] %s teleported to X: %.2f Y: %.2f Z: %.2f VW: %d INT: %d", Nome(playerid), x, y, z, vw, interior);
    escrever_log_admin(str);
    
    return 1;
}

forward AdminGotoPos(playerid, Float:x, Float:y, Float:z, vw, interior);
public AdminGotoPos(playerid, Float:x, Float:y, Float:z, vw, interior)
{
    // Set new position and interior
    SetPlayerVirtualWorld(playerid, vw);
    SetPlayerInterior(playerid, interior);
    SetPlayerPos(playerid, x, y, z);
    
    // Reset immunity flags after 3 seconds
    SetTimerEx("ResetAdminTeleport", 3000, false, "d", playerid);
    
    // Unfreeze player
    TogglePlayerControllable(playerid, 1);
    
    ms(playerid, 4, "Teleport berhasil!");
    return 1;
}

forward ResetAdminTeleport(playerid);
public ResetAdminTeleport(playerid)
{
    // Reset immunity flags
    DeletePVar(playerid, "ignorar_gelo");
    DeletePVar(playerid, "emcombate"); 
    invuneravel[playerid] = 0;
    return 1;
}

CMD:trazer(playerid, params[])
{
	if(AdminPlayer(playerid) == 0) return ms(playerid, 0, "Anda bukan admin!");
	new sss[300], id;
	if(Modo[playerid] != 1) return ms(playerid, 0, "You must be in Story mode to do this!");
	if(sscanf(params, "u", id)) return ms(playerid, 0, "Use: /ir [ ID/Nick ]");
	if(!Online(id)) return ms(playerid, 0, "This player is not online.");
    if(tv_player[id] != -1) return ms(playerid, 0, "This player is spectating someone!");
	if(Modo[id] != 1) return ms(playerid, 0, "This player must be in Story mode to do this!");
	if(olhando_camera[playerid] != -1) return ms(playerid, 0, "You are currently observing a camera!");
	if(olhando_camera[id] != -1) return ms(playerid, 0, "This player is currently observing a camera!");
	format(string_prox, 300, "Admin %s brought %s to him", Nome(playerid), Nome(id));
	ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
	LevarPlayer(id, playerid);
	format(sss, 300, "Admin %s brought you to him.", Nome(playerid));
	ms(id, 4, sss);
	return 1;
}

CMD:voippc(playerid, params[])
{
	ms(playerid, 3, "Link: [ encurtador.com.br/pqQSU ]");
	ms(playerid, 3, "This link directs to Google Drive.");
	ms(playerid, 3, "After extracting the file, open Notepad.");
	return 1;
}

CMD:help(playerid, params[])
{
    String_Gigante[0] = EOS;
    strcat(String_Gigante, "Sistem dan Informasi\n");
    strcat(String_Gigante, "Perintah Penting\n");
    strcat(String_Gigante, "Tombol yang Digunakan\n");
    strcat(String_Gigante, "Kotak Loot\n");
    strcat(String_Gigante, "Bantuan Base\n");
    strcat(String_Gigante, "Peralatan dan Material\n");
    strcat(String_Gigante, "Peta dan GPS\n");
    strcat(String_Gigante, "Kendaraan\n");
    strcat(String_Gigante, "Bagasi\n");
    strcat(String_Gigante, "Respawn Otomatis\n");
    strcat(String_Gigante, "Jadwal Raid\n");
    strcat(String_Gigante, "Bantuan Zombie\n");
    strcat(String_Gigante, "Sistem Kematian\n");
    // TAMBAHKAN LAGI //


    ShowPlayerDialog_(playerid, DIALOG_AJUDA, DIALOG_STYLE_LIST, "Bantuan", String_Gigante, "Ok", "Tutup");
    return 1;
}


CMD:listitems(playerid, params[])
{
	if(AdminPlayer(playerid) == 6) return ms(playerid, 0, "Anda bukan admin!");
	mostrar_lista_items(playerid);
	return 1;
}


CMD:CMD(playerid, params[])
{
	String_Gigante[0] = EOS;
	strcat(String_Gigante, "\n");
	for(new i; i<sizeof(ComandosPlayers); i++)
	{
	    strcat(String_Gigante, "{ffffff}");
	    strcat(String_Gigante, ComandosPlayers[i][c_Comando]);
	    strcat(String_Gigante, "  {a1a1a1}");
	    strcat(String_Gigante, ComandosPlayers[i][c_Info]);
	    strcat(String_Gigante, "\n");
	}
    ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_STYLE_MSGBOX, "Harus Di dalam mode Dayz", String_Gigante, "Ok", "Kembali");
	return 1;
}

CMD:vehiclehelp(playerid, params[])
{
    new sss[1000];
	strcat(sss, "{ffffff}/carmenu	{a1a1a1}Open the list of vehicles you own.\n");
	strcat(sss, "{ffffff}/motor	{a1a1a1}Turn the vehicle engine on or off.\n");
	strcat(sss, "{ffffff}/farol	{a1a1a1}Turn the vehicle lights on or off.\n");
	strcat(sss, "{ffffff}/capo	{a1a1a1}Open or close the engine hood.\n");
	strcat(sss, "{ffffff}/malas	{a1a1a1}Open or close the vehicle trunk.\n");
	ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_STYLE_MSGBOX, "Vehicle Help", sss, "Ok", "Close");
	return 1;
}


CMD:carmenu(playerid, params[])
{
    mostrar_veiculos(playerid, 0);
	return 1;
}

CMD:ajudamercadonegro(playerid, params[])
{
    new sss[1000];
	strcat(sss, "{ffffff}/irmercadonegro	{a1a1a1}To go to a Black Market.\n");
	strcat(sss, "{ffffff}/criarmercadonegro	{a1a1a1}To create a new Black Market.\n");
	strcat(sss, "{ffffff}/destruirmercadonegro	{a1a1a1}To destroy an existing Black Market.\n");
	strcat(sss, "{ffffff}/entradamercadonegro	{a1a1a1}To edit the entrance of a black market.\n");
	strcat(sss, "{ffffff}/saidamercadonegro	{a1a1a1}To edit the exit of a black market.\n");
	strcat(sss, "{ffffff}/interiormercadonegro	{a1a1a1}To change the Interior ID of a black market.\n");
	ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_STYLE_MSGBOX, "Commands for Black Market", sss, "Ok", "Close");
	return 1;
}

CMD:irmercadonegro(playerid, params[])
{
	new i;
    if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /irmercadonegro [ID].");
    if(i < 0 || i >= MAX_MERCADO_NEGRO ) return ms(playerid, 0, "Invalid Black Market ID!");
    if(MercadoNegro[i][mn_Existe] == 0) return ms(playerid, 0, "Invalid Black Market ID!");
    SetPlayerPos(playerid, MercadoNegro[i][mn_EntrarX], MercadoNegro[i][mn_EntrarY], MercadoNegro[i][mn_EntrarZ]);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	new sss[150];
    format(sss, 150, "You went to Black Market ID: %d.", i);
    ms(playerid, 4, sss);
	return 1;
}

CMD:interiormercadonegro(playerid, params[])
{
	new i, id;
    if(sscanf(params, "dd", i, id)) return ms(playerid, 2, "Use: /interiormercadonegro [ID] [Interior ID].");
    if(i < 0 || i >= MAX_MERCADO_NEGRO ) return ms(playerid, 0, "Invalid Black Market ID!");
    if(MercadoNegro[i][mn_Existe] == 0) return ms(playerid, 0, "Invalid Black Market ID!");
    MercadoNegro[i][mn_Interior] = id;
	atualizar_mercadonegro(i);
	salvar_mercadonegro(i);
	new sss[150];
    format(sss, 150, "Interior ID of Black Market ID: %d changed to '%d' successfully!", i, id);
    ms(playerid, 4, sss);
	return 1;
}

CMD:saidamercadonegro(playerid, params[])
{
	new i;
    if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /saidamercadonegro [ID].");
    if(i < 0 || i >= MAX_MERCADO_NEGRO ) return ms(playerid, 0, "Invalid Black Market ID!");
    if(MercadoNegro[i][mn_Existe] == 0) return ms(playerid, 0, "Invalid Black Market ID!");
	GetPlayerPos(playerid, MercadoNegro[i][mn_SairX], MercadoNegro[i][mn_SairY], MercadoNegro[i][mn_SairZ]);
    atualizar_mercadonegro(i);
	salvar_mercadonegro(i);
	new sss[150];
    format(sss, 150, "Exit location of Black Market ID: %d saved successfully!", i);
    ms(playerid, 4, sss);
	return 1;
}

CMD:entradamercadonegro(playerid, params[])
{
	new i;
    if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /entradamercadonegro [ID].");
    if(i < 0 || i >= MAX_MERCADO_NEGRO ) return ms(playerid, 0, "Invalid Black Market ID!");
    if(MercadoNegro[i][mn_Existe] == 0) return ms(playerid, 0, "Invalid Black Market ID!");
	GetPlayerPos(playerid, MercadoNegro[i][mn_EntrarX], MercadoNegro[i][mn_EntrarY], MercadoNegro[i][mn_EntrarZ]);
    atualizar_mercadonegro(i);
	salvar_mercadonegro(i);
	new sss[150];
    format(sss, 150, "Entrance location of Black Market ID: %d saved successfully!", i);
    ms(playerid, 4, sss);
	return 1;
}

CMD:destruirmercadonegro(playerid, params[])
{
	new i;
    if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /destruirmercadonegro [ID].");
    if(i < 0 || i >= MAX_MERCADO_NEGRO ) return ms(playerid, 0, "Invalid Black Market ID!");
    if(MercadoNegro[i][mn_Existe] == 0) return ms(playerid, 0, "Invalid Black Market ID!");
    MercadoNegro[i][mn_Existe] = 0;
    atualizar_mercadonegro(i);
	salvar_mercadonegro(i);
	new sss[150];
    format(sss, 150, "Black Market ID: %d Destroyed successfully!", i);
    ms(playerid, 4, sss);
	return 1;
}

CMD:criarmercadonegro(playerid, params[])
{
    for(new i; i<MAX_MERCADO_NEGRO; i++)
	{
	    if(MercadoNegro[i][mn_Existe] == 0)
	    {
	        MercadoNegro[i][mn_Existe] = 1;
	        GetPlayerPos(playerid, MercadoNegro[i][mn_EntrarX], MercadoNegro[i][mn_EntrarY], MercadoNegro[i][mn_EntrarZ]);
	        MercadoNegro[i][mn_SairX] = 286.148986;
	        MercadoNegro[i][mn_SairY] = -40.644397;
	        MercadoNegro[i][mn_SairZ] = 1001.515625;
	        MercadoNegro[i][mn_Interior] = 1;

	        new sss[150];
	        format(sss, 150, "Black Market ID: %d created! Use: /ajudamercadonegro for more commands.", i);
	        ms(playerid, 4, sss);
	        atualizar_mercadonegro(i);
	        salvar_mercadonegro(i);
	        return 1;
	    }
	}
	ms(playerid, 0, "Maximum number of Black Markets reached!");
	return 1;
}

CMD:aa(playerid, params[])
{
	new cc;
	String_Gigante[0] = EOS;
	strcat(String_Gigante, "\n\n");


	cc = 0;
	strcat(String_Gigante, "{00ffff}COMANDOS ADMIN 1:{ffffff}\n");
	for(new a1; a1<sizeof ComandosAdmin; a1++)
	{
	    if(ComandosAdmin[a1][cmd_Level] == 1)
	    {
	        strcat(String_Gigante, ComandosAdmin[a1][cmd_Comando]);
	        strcat(String_Gigante, "  ");
	        cc++;
	        if(cc == 7) strcat(String_Gigante, "\n"), cc = 0;
	    }
	}

	cc = 0;
	strcat(String_Gigante, "\n\n{00ffff}COMANDOS ADMIN 2:{ffffff}\n");
	for(new a2; a2<sizeof ComandosAdmin; a2++)
	{
	    if(ComandosAdmin[a2][cmd_Level] == 2)
	    {
	        strcat(String_Gigante, ComandosAdmin[a2][cmd_Comando]);
	        strcat(String_Gigante, "  ");
	        cc++;
	        if(cc == 7) strcat(String_Gigante, "\n"), cc = 0;
	    }
	}

	cc = 0;
	strcat(String_Gigante, "\n\n{00ffff}COMANDOS ADMIN 3:{ffffff}\n");
	for(new a3; a3<sizeof ComandosAdmin; a3++)
	{
	    if(ComandosAdmin[a3][cmd_Level] == 3)
	    {
	        strcat(String_Gigante, ComandosAdmin[a3][cmd_Comando]);
	        strcat(String_Gigante, "  ");
	        cc++;
	        if(cc == 7) strcat(String_Gigante, "\n"), cc = 0;
	    }
	}

	cc = 0;
	strcat(String_Gigante, "\n\n{00ffff}COMANDOS ADMIN 4:{ffffff}\n");
	for(new a4; a4<sizeof ComandosAdmin; a4++)
	{
	    if(ComandosAdmin[a4][cmd_Level] == 4)
	    {
	        strcat(String_Gigante, ComandosAdmin[a4][cmd_Comando]);
	        strcat(String_Gigante, "  ");
	        cc++;
	        if(cc == 7) strcat(String_Gigante, "\n"), cc = 0;
	    }
	}

	cc = 0;
	strcat(String_Gigante, "\n\n{00ffff}COMANDOS ADMIN 5:{ffffff}\n");
    for(new a5; a5<sizeof ComandosAdmin; a5++)
	{
	    if(ComandosAdmin[a5][cmd_Level] == 5)
	    {
	        strcat(String_Gigante, ComandosAdmin[a5][cmd_Comando]);
	        strcat(String_Gigante, "  ");
	        cc++;
	        if(cc == 7) strcat(String_Gigante, "\n"), cc = 0;
	    }
	}

	cc = 0;
	strcat(String_Gigante, "\n\n{00ffff}COMANDOS ADMIN 6:{ffffff}\n");
    for(new a6; a6<sizeof ComandosAdmin; a6++)
	{
	    if(ComandosAdmin[a6][cmd_Level] == 6)
	    {
	        strcat(String_Gigante, ComandosAdmin[a6][cmd_Comando]);
	        strcat(String_Gigante, "  ");
	        cc++;
	        if(cc == 7) strcat(String_Gigante, "\n"), cc = 0;
	    }
	}

	cc = 0;
	strcat(String_Gigante, "\n\n{00ffff}COMANDOS ADMIN 7:{ffffff}\n");
    for(new a7; a7<sizeof ComandosAdmin; a7++)
	{
	    if(ComandosAdmin[a7][cmd_Level] == 7)
	    {
	        strcat(String_Gigante, ComandosAdmin[a7][cmd_Comando]);
	        strcat(String_Gigante, "  ");
	        cc++;
	        if(cc == 7) strcat(String_Gigante, "\n"), cc = 0;
	    }
	}

	cc = 0;
	strcat(String_Gigante, "\n\n{00ffff}COMANDOS ADMIN 8:{ffffff}\n");
    for(new a8; a8<sizeof ComandosAdmin; a8++)
	{
	    if(ComandosAdmin[a8][cmd_Level] == 8)
	    {
	        strcat(String_Gigante, ComandosAdmin[a8][cmd_Comando]);
	        strcat(String_Gigante, "  ");
	        cc++;
	        if(cc == 7) strcat(String_Gigante, "\n"), cc = 0;
	    }
	}

	strcat(String_Gigante, "\n\n");
	ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_VAZIO, "{ffff00}Comandos Admin", String_Gigante, "Ok", "Fechar");
	return 1;
}

CMD:ajudaactors(playerid, params[])
{
    new sss[1000];
	strcat(sss, "{ffffff}/iractor {a1a1a1}To go to an Actor.\n");
	strcat(sss, "{ffffff}/copiaractor {a1a1a1}To copy an Actor and create another one.\n");
	strcat(sss, "{ffffff}/criaractor {a1a1a1}To create a new Actor.\n");
	strcat(sss, "{ffffff}/destruiractor	{a1a1a1}To destroy an existing Actor.\n");
	strcat(sss, "{ffffff}/actor	{a1a1a1}To get the ID of a nearby actor.\n");
	strcat(sss, "{ffffff}/skinactor	{a1a1a1}To change the Skin of an Actor.\n");
	strcat(sss, "{ffffff}/nomeactor	{a1a1a1}To change the Name of an Actor.\n");
	strcat(sss, "{ffffff}/animactor	{a1a1a1}To change the Animation of an Actor.\n");
	strcat(sss, "{ffffff}/trazeractor {a1a1a1}To change the Position of an Actor.\n");
	ShowPlayerDialog_(playerid, DIALOG_VAZIO, DIALOG_STYLE_MSGBOX, "Commands for Actors", sss, "Ok", "Close");
	return 1;
}

CMD:copiaractor(playerid, params[])
{
    new i;
    if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /copiaractor [ID].");
	if(i < 0 || i >= MAX_BOOTS) return ms(playerid, 0, "Invalid Actor ID!");
	if(Actor[i][a_Existe] == 0) return ms(playerid, 0, "Invalid Actor ID!");

	for(new a; a<MAX_BOOTS; a++)
	{
		if(Actor[a][a_Existe] == 0)
		{
		    Actor[a][a_Existe] = 1;
        	Actor[a][a_Skin] = Actor[i][a_Skin];
            format(Actor[a][a_Nome], MAX_PLAYER_NAME, Actor[i][a_Nome]);
            format(Actor[a][a_Anim1], MAX_PLAYER_NAME, Actor[i][a_Anim1]);
            format(Actor[a][a_Anim2], MAX_PLAYER_NAME, Actor[i][a_Anim2]);
            Actor[a][a_Animacao] = Actor[i][a_Animacao];
			GetPlayerPos(playerid, Actor[a][a_X],Actor[a][a_Y],Actor[a][a_Z]);
			GetPlayerFacingAngle(playerid, Actor[a][a_A]);
            Actor[a][a_Mundo] = GetPlayerVirtualWorld(playerid);
			Actor[a][a_Interior] = GetPlayerInterior(playerid);
			atualizar_actor(a);
    		salvar_actor(a);
			new sss[150];
    		format(sss, 150,"You copied Actor ID %d, and created Actor ID:%d." , i, a);
			ms(playerid, 4, sss);
			return 1;
		}
	}
	ms(playerid, 0, "Maximum number of Actors reached!");
	return 1;
}

CMD:animactor(playerid, params[])
{
    new i, anim1[40],anim2[40], an;
    if(sscanf(params, "dds[40]s[40]", i, an, anim1, anim2)) return ms(playerid, 2, "Use: /animactor [ID] [1 = yes, 0 = no] [anim1] [anim2].");
	if(i < 0 || i >= MAX_BOOTS) return ms(playerid, 0, "Invalid Actor ID!");
	if(Actor[i][a_Existe] == 0) return ms(playerid, 0, "Invalid Actor ID!");
    Actor[i][a_Animacao] = an;
	format(Actor[i][a_Anim1], 40, anim1 );
	format(Actor[i][a_Anim2], 40, anim2 );
    atualizar_actor(i);
    salvar_actor(i);
    new sss[150];
    format(sss, 150, "You changed the Actor Animation.");
	ms(playerid, 4, sss);
	return 1;
}

CMD:iractor(playerid, params[])
{
    new i;
    if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /iractor [ID].");
	if(i < 0 || i >= MAX_BOOTS) return ms(playerid, 0, "Invalid Actor ID!");
	if(Actor[i][a_Existe] == 0) return ms(playerid, 0, "Invalid Actor ID!");
	SetPlayerPos(playerid, Actor[i][a_X], Actor[i][a_Y], Actor[i][a_Z]);
	SetPlayerInterior(playerid, Actor[i][a_Interior]);
	SetPlayerVirtualWorld(playerid, Actor[i][a_Mundo]);
    new sss[150];
    format(sss, 150,"You went to Actor ID %d." , i);
	ms(playerid, 4, sss);
	return 1;
}

CMD:trazeractor(playerid, params[])
{
    new i;
    if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /nomeactor [ID].");
	if(i < 0 || i >= MAX_BOOTS) return ms(playerid, 0, "Invalid Actor ID!");
	if(Actor[i][a_Existe] == 0) return ms(playerid, 0, "Invalid Actor ID!");
	GetPlayerPos(playerid, Actor[i][a_X], Actor[i][a_Y], Actor[i][a_Z]);
	GetPlayerFacingAngle(playerid, Actor[i][a_A]);
    atualizar_actor(i);
    salvar_actor(i);
    new sss[150];
    format(sss, 150, "You changed the Position of Actor ID %d." , i);
	ms(playerid, 4, sss);
	return 1;
}

CMD:nomeactor(playerid, params[])
{
    new i, nome[MAX_PLAYER_NAME];
    if(sscanf(params, "ds[24]", i, nome)) return ms(playerid, 2, "Use: /nomeactor [Actor ID use /actor] [Name].");
	if(i < 0 || i >= MAX_BOOTS) return ms(playerid, 0, "Invalid Actor ID!");
	if(Actor[i][a_Existe] == 0) return ms(playerid, 0, "Invalid Actor ID!");
	format(Actor[i][a_Nome], MAX_PLAYER_NAME, nome );
    atualizar_actor(i);
    salvar_actor(i);
    new sss[150];
    format(sss, 150, "You changed the Name of Actor ID %d, to skin: '%s'.", i, nome);
	ms(playerid, 4, sss);
	return 1;
}

CMD:skinactor(playerid, params[])
{
    new i, skin;
    if(sscanf(params, "dd", i, skin)) return ms(playerid, 2, "Use: /skinactor [ID do Actor use /actor] [ID da skin].");
	if(i < 0 || i >= MAX_BOOTS) return ms(playerid, 0, "Invalid Actor ID!");
	if(Actor[i][a_Existe] == 0) return ms(playerid, 0, "Invalid Actor ID!");
	if(skin < 0 || skin > 311) return ms(playerid, 0, "Invalid Skin ID! Use from 0 - 311.");
	Actor[i][a_Skin] = skin;
    atualizar_actor(i);
    salvar_actor(i);
    new sss[150];
    format(sss, 150, "You changed the Skin of Actor ID %d, to skin: %d.", i, skin);
	ms(playerid, 4, sss);
	return 1;
}

CMD:actor(playerid, params[])
{
    for(new i; i<MAX_BOOTS; i++)
	{
		if(Actor[i][a_Existe] == 1)
		{
		    if(IsPlayerInRangeOfPoint(playerid, 5, Actor[i][a_X],Actor[i][a_Y],Actor[i][a_Z]))
		    {
		        if(GetPlayerInterior(playerid) == Actor[i][a_Interior])
		        {
		            if(GetPlayerVirtualWorld(playerid) == Actor[i][a_Mundo])
		            {
	            		new sss[150];
			    		format(sss, 150, "Actor de ID %d, Nome: %s.", i, Actor[i][a_Nome]);
						ms(playerid, 4, sss);
						return 1;
					}
				}
			}
		}
	}
	ms(playerid, 0, "No Actor near you!");
	return 1;
}

CMD:destruiractor(playerid, params[])
{
    new i;
    if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /destruiractor [Actor ID use /actor].");
	if(i < 0 || i >= MAX_BOOTS) return ms(playerid, 0, "Invalid Actor ID!");
	if(Actor[i][a_Existe] == 0) return ms(playerid, 0, "Invalid Actor ID!");
    destruir_actor(i);
    new sss[150];
    format(sss, 150, "You destroyed Actor ID %d.", i);
	ms(playerid, 4, sss);
	return 1;
}

CMD:criaractor(playerid, params[])
{
    new sss[150];
    new Float:p[4];
    new nome[MAX_PLAYER_NAME], skin;
    GetPlayerPos(playerid, p[0], p[1], p[2]);
    GetPlayerFacingAngle(playerid, p[3]);
    if(sscanf(params, "ds[24]", skin, nome)) return ms(playerid, 2, "Use: /actor [skin] [Name].");
    if(skin < 0 || skin > 311) return ms(playerid, 0, "Invalid Skin ID! Use from 0 - 311.");
	new a = criar_actor(p[0], p[1], p[2], p[3], nome, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), skin);
	format(sss, 150, "New Actor created ID: %d! Use /ajudaactors to see the commands.", a);
	ms(playerid, 4, sss);
	return 1;
}

CMD:motor(playerid, params[])
{
	if(!IsPlayerInAnyVehicle(playerid)) return ms(playerid, 0, "You are not in a vehicle!");
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER ) return ms(playerid, 0,  "You are not the driver of the vehicle!");
	if(RC[playerid] == GetPlayerVehicleID(playerid)) return ms(playerid, 0,  "This vehicle does not have an engine!");
	if(carro_ferro_velho(GetPlayerVehicleID(playerid)) != -1)  return ms(playerid, 0,  "This vehicle does not have an engine!");
 	if(VeiculoBicicleta(GetPlayerVehicleID(playerid))) return ms(playerid, 0,  "This vehicle does not have an engine!");
 	new car = GetPlayerVehicleID(playerid);
	new Float:vidacarro;
	GetVehicleHealth(car, vidacarro);
	if(vidacarro <= 300.0 ) return ms(playerid, 0, "This vehicle is too damaged, needs engine repair!");
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
	if(engine == 0)SetVehicleParamsEx(GetPlayerVehicleID(playerid), 1, lights, alarm, doors, bonnet, boot, objective);
	else SetVehicleParamsEx(GetPlayerVehicleID(playerid), 0, lights, alarm, doors, bonnet, boot, objective);
	if(engine == 0)
	{
        format(string_prox, 120, " %s turned on the engine of their vehicle ",Nome(playerid));
		ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
	}
	else
	{
        format(string_prox, 120, " %s turned off the engine of their vehicle ",Nome(playerid));
		ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
	}
	return 1;
}

CMD:farol(playerid, params[])
{
	if(!IsPlayerInAnyVehicle(playerid)) return ms(playerid, 0, "You are not in a vehicle!");
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER ) return ms(playerid, 0, "You are not the driver of the vehicle!");
 	if(RC[playerid] == GetPlayerVehicleID(playerid)) return ms(playerid, 0,  "This vehicle does not have a headlight!");
	if(VeiculoBicicleta(GetPlayerVehicleID(playerid))) return ms(playerid, 0, "This vehicle does not have a headlight!");
	if(carro_ferro_velho(GetPlayerVehicleID(playerid)) != -1)  return ms(playerid, 0,  "This vehicle does not have a battery!");
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
	if(lights == 0)SetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, 1, alarm, doors, bonnet, boot, objective);
	else SetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, 0, alarm, doors, bonnet, boot, objective);
	if(lights == 0)
	{
        format(string_prox, 120, " %s ligou o farol de seu veiculo ",Nome(playerid));
		ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
	}
	else
	{
        format(string_prox, 120, " %s desligou o farol de seu veiculo ",Nome(playerid));
		ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
	}
	return 1;
}

CMD:malas(playerid, params[])
{
	if(!IsPlayerInAnyVehicle(playerid)) return ms(playerid, 0, "You are not in a vehicle!");
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER ) return ms(playerid, 0, "You are not the driver of the vehicle!");
 	if(RC[playerid] == GetPlayerVehicleID(playerid)) return ms(playerid, 0,  "This vehicle does not have a trunk!");
    if(carro_ferro_velho(GetPlayerVehicleID(playerid)) != -1)  return ms(playerid, 0,  "This vehicle must be mounted first!");
	if(VeiculoAviao(GetPlayerVehicleID(playerid)) || VeiculoBarco(GetPlayerVehicleID(playerid))
    || VeiculoMoto(GetPlayerVehicleID(playerid)) || VeiculoBicicleta(GetPlayerVehicleID(playerid))) return ms(playerid, 0, "This vehicle does not have a trunk");
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
	if(boot == 0)SetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, 1, objective);
	else SetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, 0, objective);
	if(boot == 0)
	{
        format(string_prox, 120, " %s abriu o porta-malas de seu veiculo ",Nome(playerid));
		ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
	}
	else
	{
        format(string_prox, 120, " %s fechou o porta-malas de seu veiculo ",Nome(playerid));
		ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
	}
	return 1;
}

CMD:capo(playerid, params[])
{
	if(!IsPlayerInAnyVehicle(playerid)) return ms(playerid, 0, "You are not in a vehicle!");
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER ) return ms(playerid, 0, "You are not the driver of this vehicle!");
 	if(RC[playerid] == GetPlayerVehicleID(playerid)) return ms(playerid, 0,  "This vehicle does not have a hood!");
 	if(carro_ferro_velho(GetPlayerVehicleID(playerid)) != -1)  return ms(playerid, 0,  "This vehicle must be mounted first!");
 	if(VeiculoAviao(GetPlayerVehicleID(playerid)) || VeiculoBarco(GetPlayerVehicleID(playerid))
 	|| VeiculoMoto(GetPlayerVehicleID(playerid)) || VeiculoBicicleta(GetPlayerVehicleID(playerid))) return ms(playerid, 0, "This vehicle does not have a hood");
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
	if(bonnet == 0)SetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, 1, boot, objective);
	else SetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, 0, boot, objective);
	if(bonnet == 0)
	{
        format(string_prox, 120, " %s abriu o capo de seu veiculo ",Nome(playerid));
		ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
	}
	else
	{
        format(string_prox, 120, " %s fechou o capo de seu veiculo ",Nome(playerid));
		ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
	}
	return 1;
}


CMD:destruirveiculo(playerid, params[])
{
	new i;
    if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /destruirveiculo [ ID ].");
	if(GetVehicleModel(i) == 0)  return ms(playerid, 0, "This vehicle does not exist.");
    ms(playerid, 1, "You destroyed this vehicle.");
    DestruirVeiculo(i);
	return 1;
}

CMD:criarveiculo(playerid, params[])
{
	new dono;
	new model;
	new c1,c2;
	new Float:pos[4];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);
	if(sscanf(params, "dudd", model, dono, c1, c2)) return ms(playerid, 2, "Use: /criarveiculo [modelo] [ ID/Nick ] [cor 1] [cor 2]");
    if(!Online(dono)) return ms(playerid, 0, "This player is not online!");
	if(model < 400 || model > 611) return ms(playerid, 0, "Use um modelo de 400 - 611 !");
	new idv = CriarVeiculo(1, model, pos[0], pos[1], pos[2], pos[3], c1, c2, Nome(dono));
    ms(playerid, 4, "You created a new vehicle.");
    PutPlayerInVehicle(playerid, idv, 0);
    SalvarVeiculo(idv);
	return 1;
}


CMD:radio(playerid, params[])
{
    if(!tem_item(playerid, 100)) return ms(playerid, 0, "You do not have a Radio Communicator in your Inventory!");
	mostrar_radio(playerid);
	return 1;
}

CMD:particular(playerid, params[]) return cmd_par(playerid, params);
CMD:par(playerid, params[])
{
	new mens[128], id, string[500];
	if(sscanf(params, "us[128]", id, mens)) return ms(playerid, 2, "Use: /par [ID/Nick] [message]."), ms(playerid, 3, "Used to send a Private message.");
	if(!Online(id)) return ms(playerid, 0, "This player is not online!");
	if(id == playerid) return ms(playerid, 0, "You cannot send a private message to yourself!");
	if(pInfo[playerid][pConfig][4] == 1) return ms(playerid, 0, "You disabled this system in /settings!");
	if(pInfo[id][pConfig][4] == 1) return ms(playerid, 0, "This player disabled this system in /settings!");
    if(ModoAdmin[playerid] == 0 && ModoAdmin[id] == 0 && !tem_item(playerid, 100)) return ms(playerid, 0, "You do not have a Radio Communicator in your Inventory!");
	if(ModoAdmin[playerid] == 0 && ModoAdmin[id] == 0 && !tem_item(id, 100)) return ms(playerid, 0, "This player does not have a Radio Communicator in Inventory!");

	if(AdminPlayer(playerid) == 0) // se for player //
	{
		format(string, 500, "[PARTICULAR] %s[%d]: %s", Nome(playerid), playerid, mens);
		SendClientMessage(id, 0xffff00ff, string);
		format(string, 500, "Enviado - %s[%d]: %s", Nome(id), id, mens);
		SendClientMessage(playerid, 0x00ffffff, string);
		return 1;
 	}

	format(string, 500, "[ADMIN] %s[%d]: %s", Nome(playerid), playerid, mens);
	SendClientMessage(id, 0xffff00ff, string);
	format(string, 500, "Enviado - %s[%d]: %s", Nome(id), id, mens);
	SendClientMessage(playerid, 0x00ffffff, string);
	return 1;
}

CMD:a(playerid, params[])
{
	new mens[128], string[500];
	if(sscanf(params, "s[128]", mens)) return ms(playerid, 2, "Use: /a [message]."), ms(playerid, 3, "Used to send a message in the Admin chat.");
	new i = AdminID(playerid);
	format(string, 500, "[Admin - %s] %s: %s", Admin[i][adm_Funcao], Nome(playerid), mens);
	for(new id; id<MAX_PLAYERS; id++) if(Online(id)) if(AdminPlayer(id) != 0) ms(id, 5, string);
	return 1;
}

CMD:av(playerid, params[])
{
    new sss[500], motivo[128];
    if(sscanf(params, "s[128]", motivo )) return ms(playerid, 2, "Use: /av [ Menssagem ]");
    new i = AdminID(playerid);
	SendClientMessageToAll(0xF0E68Cff, "x~~~~~~~~~~~~~~~~~~~~~~x {FFFFFF}Administrative Warning{F0E68C} x~~~~~~~~~~~~~~~~~~~~~~x");
   	format(sss, 500, "%s {ffffff}%s{a1a1a1}: %s", Admin[i][adm_Funcao], Nome(playerid), motivo);
   	SendClientMessageToAll(0xF0E68CFF, sss);
	return 1;
}


CMD:cb(playerid, params[])
{
	new b = BasePlayer(playerid);
	if(b == -1) return ms(playerid, 0, "You are not part of a base!");
	if(pInfo[playerid][pConfig][1] == 1) return ms(playerid, 0, "You disabled this Chat in /settings!");
	new mens[128], string[300];
	if(sscanf(params, "s[128]", mens)) return ms(playerid, 2, "Use: /cb [message]."), ms(playerid, 3, "Used to send a message to base players who are Online.");
	format(string, 200, "{ffffff}[ {00ffff}/cb{ffffff} ] {ffff00}%s [%d]: {00ffff}%s",Nome(playerid), playerid, mens);
    for(new i; i<MAX_PLAYERS; i++)
	{
	    if(Online(i))
	    {
	        if(BasePlayer(i) != b) continue;
	        if(pInfo[i][pConfig][1] == 1) continue;
			ms(i, 4, string);
	    }
	}
	return 1;
}

CMD:portoes(playerid, params[])
{
    if(BasePlayer(playerid) == -1) return ms(playerid, 0, "You are not part of a base!");
    if(Modo[playerid] == 1)
	{
	    String_Gigante[0] = EOS;
		new cont;
		new string[150];
		strcat(String_Gigante, "Portao ID\tVida\tDistancia\n");
		new Float:dis;
		new Float:pos[3];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		for(new i; i<MAX_PORTOES; i++)
		{
		    Lista_Portao[playerid][i] = -1;
		    if(Portao[i][portao_Existe] == 0) continue;
		    if(Portao[i][portao_Base] == BasePlayer(playerid))
		    {
		        GetDistance(dis, pos[0], pos[1], pos[2], Portao[i][portao_X1], Portao[i][portao_Y1], Portao[i][portao_Z1]);
		        format(string, 150, "Portao %d\t%d%%\t%.0f Metros\n", i, Portao[i][portao_Vida], dis);
		        strcat(String_Gigante, string);
				Lista_Portao[playerid][cont] = i;
		        cont ++;
  			}
		}
		format(string, 150, "{ffffff}Portoes da Base [{a1a1a1}%d{ffffff}]", cont);
	    ShowPlayerDialog_(playerid, DIALOG_PORTAO5, DIALOG_STYLE_TABLIST_HEADERS, string, String_Gigante, "Continuar", "Fechar");
	}
	return 1;
}

CMD:portao(playerid, params[])
{
	if(BasePlayer(playerid) == -1) return ms(playerid, 0, "You are not part of a base!");
    if(Modo[playerid] == 1)
	{
		new i;
		if(sscanf(params, "d", i)) return ms(playerid, 2, "Use: /portao [id do portao].");
		if(i < 0 || i >= MAX_PORTOES) return ms(playerid, 0, "Invalid Gate ID!");
		if(Portao[i][portao_Existe] == 0) return ms(playerid, 0, "This gate does not exist!");
		if(Portao[i][portao_Base] != BasePlayer(playerid)) return ms(playerid, 0, "This gate does not belong to your Base!");
		MostrarPortao(playerid, i);
	}
	return 1;
}

CMD:abrirportao(playerid, params[])
{
    if(Modo[playerid] == 1)
	{
		for(new i; i<MAX_PORTOES; i++)
		{
		    if(Portao[i][portao_Existe] == 0) continue;
	        if(IsPlayerInRangeOfPoint(playerid, 4.5, Portao[i][portao_X1],Portao[i][portao_Y1],Portao[i][portao_Z1]))
	        {
	            if(GetPlayerInterior(playerid) == Portao[i][portao_Interior] && GetPlayerVirtualWorld(playerid) ==  Portao[i][portao_Mundo])
	            {
	                if(portao_base(playerid, i)) abrir_portao(i);
	                else usar_senha_portao(playerid, i);
	                return 1;
	            }
	        }
		}
	}
	return 1;
}

CMD:base(playerid, params[])
{
    if(Modo[playerid] == 1)
	{
		new i = BasePlayer(playerid);
		if(i == -1) return ms(playerid, 0, "You are not part of a base.");
	    if(IsPlayerInRangeOfPoint(playerid, 50.0, Base[i][base_X], Base[i][base_Y], Base[i][base_Z]))
		{
			MenuBase(playerid, i);
		    return 1;
		}
		else
		{
		    Localizar_Player(playerid, Base[i][base_X], Base[i][base_Y], Base[i][base_Z], 4, i);
		    ms(playerid, 1, "Base marcada em vermelho no mapa !");
		}
	}
	return 1;
}

CMD:aceitarpedido(playerid, params[])
{
    if(Modo[playerid] == 1)
	{
		new id;
		new str[150];
		new i = BasePlayer(playerid);
		if(DonoBase(playerid) == -1 && SubBase(playerid) == -1) return ms(playerid, 0, "You are not Owner or Sub of a Base.");
	    if(sscanf(params, "u", id)) return ms(playerid, 2, "Use: /aceitarpedido [Nick/ID].");
		if(!Online(id)) return ms(playerid, 0, "This player is not online.");
		if(BasePlayer(id) != -1) return ms(playerid, 0, "This player is already part of a base.");
		if(GetPVarInt(id, "entrar_base") != i ) return ms(playerid, 0, "This player did not request to join the Base recently.");

		for(new ii=3; ii<MAX_MEMBROS; ii++)
		{
		    if(Comparar(Nome(-1), Membro[i][ii]))
		    {
		        SetPVarInt(id, "entrar_base", -1);
		        SetPVarInt(id, "flood_pedir", gettime());
				format(str, 150, "The player '%s' was accepted and is now part of the base members list.", Nome(id));
				for(new p; p<MAX_PLAYERS; p++) if(Online(p)) if(BasePlayer(p) == i) ms(p, 3, str);
		        format(Membro[i][ii], MAX_PLAYER_NAME, Nome(id));
		        format(str, 150, "You were accepted and are now part of the base '%s'.", Base[i][base_Nome]);
		        ms(id, 3, str);
				salvar_base(i);
		        format(str, 200, "The Member '%s' accepted the request of '%s' to be part of the Base.", Nome(playerid), Nome(id));
		    	escrever_log_base(i, str);

		        for(new ca; ca<MAX_CAMERAS; ca++)
		        {
					if(Camera[ca][ca_Existe] == 0) continue;
	                if(Comparar(Nome(id), Camera[ca][ca_Dono]))
	                {
	                    Camera[ca][ca_Base] = i;
	                    salvar_camera(ca);
	                }
		        }
                base_player[id] = i;
                salvar_base(id);
		        return 1;
		    }
		}
		ms(playerid, 0, "The members list is full!");
	}
	return 1;
}

CMD:createbase(playerid, params[])
{
    if(AdminPlayer(playerid) == 0) return ms(playerid, 0, "You are not an admin!");
    if(tv_player[playerid] != -1)
        return ms(playerid, 0, "You cannot do this while /tv Mode is active!");
    if(Modo[playerid] == 1)
    {
        if(pInfo[playerid][pLevel] < 5)
            return ms(playerid, 0, "You need Level 5 to create a base!");
        if(BasePlayer(playerid) != -1)
            return ms(playerid, 0, "You are already in a base.");
        if(GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0)
            return ms(playerid, 0, "You cannot do this inside an interior.");

        new nome_base[40];
        new Float:p[3];
        GetPlayerPos(playerid, p[0], p[1], p[2]);

        if(sscanf(params, "s[40]", nome_base))
            return ms(playerid, 2, "Usage: /createbase [Base Name].");
        if(strlen(nome_base) < 4)
            return ms(playerid, 0, "Base name must be at least 4 characters.");

        new b = Criar_Base(p[0], p[1], p[2], nome_base, Nome(playerid));

        if(b == -1)
            ms(playerid, 0, "Maximum number of bases on the server has been reached!");
        else
        {
            new msg[200];
            format(msg, 200, "Player '%s' has created a base (%s).", Nome(playerid), nome_base);
            escrever_log_base(b, msg);
            base_player[playerid] = b;
        }
    }
    return 1;
}

Criar_Base(Float:x, Float:y, Float:z, nome_base[], base_owner[])
{
    for(new i = 0; i < MAX_BASES; i++)
    {
        if(Base[i][base_Existe] == 0)
        {
            Base[i][base_Existe] = 1;
            format(Base[i][base_Nome], 40, nome_base);
            Base[i][base_X] = x;
            Base[i][base_Y] = y;
            Base[i][base_Z] = z;
            Base[i][base_Level] = 1;
            Base[i][base_Classe] = 0;
            Base[i][base_XP] = 0;

            for(new ii = 0; ii < MAX_MEMBROS; ii++)
            {
                if(ii == 0)
                    format(Membro[i][ii], MAX_PLAYER_NAME, base_owner);
                else
                    format(Membro[i][ii], MAX_PLAYER_NAME, Nome(-1));
            }

            atualizar_base(i);

            new str[150];
            format(str, 150, "[BASES] Base baru dibuat, '%s', Pemilik: %s.", nome_base, base_owner);
            SendClientMessageToAll(0x00ffffff, str);

            format(str, 100, "Base %d", i);
            CanalBase[i] = SvCreateGStream(0xffff00ff, str);
            limpar_log_base(i);
            return i;
        }
    }
    return -1;
}




CMD:salvar(playerid, params[])
{
	new Float:p[3];
	for(new i; i<MAX_PLAYERS; i++)
	{
	    if(i == playerid) continue;
	    if(Online(i))
	    {
	        if(IsPlayerNPC(i)) continue;
	        if(Modo[i] != Modo[playerid]) continue;
			if(Morto[i] == 0) continue;
			if(Reanimando[i] != 0) continue;
			if(GetPlayerVirtualWorld(i) != GetPlayerVirtualWorld(playerid)) continue;
			if(GetPlayerInterior(i) != GetPlayerInterior(playerid)) continue;
			GetPlayerPos(i, p[0], p[1], p[2]);
			if(!IsPlayerInRangeOfPoint(playerid, 2.0, p[0], p[1], p[2])) continue;
			if(pInfo[playerid][pClasse] != 1)
			{
				if(tem_remedio(playerid) == -1 && Modo[playerid] == 1)
				{
					ms(playerid, 0, "You do not have a medicine in your Inventory!");
					return 1;
				}
			}
			SetPVarInt(playerid, "remedio", tem_remedio(playerid));
			SetPVarInt(playerid, "morto", i);
			SetPVarInt(i, "salvando", playerid);
			SetPlayerToFacePos(playerid, p[0], p[1]);

			new tempo;
			if(pInfo[playerid][pClasse] == 1) tempo = 75;
			tempo = 200;
			Acao(playerid, 5, tempo, "SALVANDO JOGADOR", 1, "COP_AMBIENT", "COPBROWSE_LOOP", 1);
			SetPlayerAttachedObject(playerid, 9, 11738, 6, 0.070000, 0.194999, -0.090999,   55.500000, -4.699998, 55.799983,   1.000000, 1.000000, 1.000000);
			mostrar_morte(i);
			break;
	    }
	}
	return 1;
}


CMD:lobby(playerid, params[])
{
	if(ModoAdmin[playerid] == 0 && GetPVarInt(playerid, "looby") > gettime())
	{
	    new sss[300];
	    format(sss, 300, "You can only return to the lobby again after %s.", ConvertTime(GetPVarInt(playerid, "looby") - gettime()));
		ms(playerid, 0, sss);
	    return 1;
	}
	if(Barra[playerid][b_Acao] != 0) return ms(playerid, 0, "You cannot return to Lobby while doing an action!");
	if(mostrando_arma[playerid] == 1) return ms(playerid, 0, "You cannot return to Lobby with weapon menu open!");
    if(invaberto[playerid] != 0) return ms(playerid, 0, "You cannot return to Lobby with inventory open!");
    if(dialog_player[playerid] != -1) return ms(playerid, 0, "You cannot return to Lobby with dialog open!");
    if(tv_player[playerid] != -1) return ms(playerid, 0, "You cannot do this in /tv Mode!");
    if(cama_player[playerid] != -1) return ms(playerid, 0, "You cannot do that in bed!");
	if(cadeira_player[playerid] != -1) return ms(playerid, 0, "You cannot do that while sitting!");
	if(IsPlayerInRangeOfPoint(playerid, 50, 1.6710,33.6036,1199.5938)) return ms(playerid, 0, "You need to jump off the plane!");
    if(GetPlayerSpeed(playerid) > 1) return ms(playerid, 0, "You need to be stopped to use this command!");
    if(Morto[playerid] > 0) return ms(playerid, 0, "You cannot return to Lobby while dead.");
	if(EmCombate(playerid)) return ms(playerid, 0, "You cannot return to Lobby while in combat.");
    format(string_prox, 300, " The player %s went to Lobby ", Nome(playerid));
	ProxDetector(10.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
	if(Modo[playerid] == 1)
	{
		for(new pla; pla<MAX_PLAYERS; pla++)
		{
		    if(Online(pla))
		    {
		        if(hackeando_id[pla] == playerid)
		        {
		            hackeando_id[pla] = -1;
				    hackeando_tempo[pla] = 0;
				    ms(pla, 3, "The player who was hacking went to Lobby, location lost!");
		        }
			}
		}

		salvarplayer(playerid);
		Modo[playerid] = 0;
		SpawnPlayer(playerid);

		for(new fr; fr<MAX_DROPS; fr++) if(Drop[fr][drop_Existe] == 1) GZ_EsconderGzPlayer(playerid, Drop[fr][drop_Gz]);
	    for(new a; a<sizeof Area; a++) GZ_EsconderGzPlayer(playerid, Area[a][area_GZ]);
	}
	return 1;
}

CMD:irpos(playerid, params[])
{
	new Float:pos[3], inter, mund;
	if(sscanf(params, "fffdd", pos[0], pos[1], pos[2], inter, mund)) return ms(playerid, 2, "Use: /irpos [X] [Y] [Z] [interior] [mundo].");
	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	SetPlayerInterior(playerid, inter);
	SetPlayerVirtualWorld(playerid, mund);
    ms(playerid, 4, "You teleported to a new position.");
	return 1;
}


CMD:setarfome(playerid, params[])
{
	new inter, id;
	new str[150];
	if(sscanf(params, "ud", id, inter)) return ms(playerid, 2, "Use: /setarfome [ID/Nick] [ 0 - 100 ].");
	if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
	if(inter < 0 || inter > 100) return ms(playerid, 0, "Use a value from 0 to 100!");
	pInfo[id][pFome] = (inter*2);
	format(str, 150, "You set the Hunger of '%s' to [%d].", Nome(id), inter);
    ms(playerid, 4, str);
    format(str, 150, "Admin '%s' set your Hunger to [%d].", Nome(playerid), inter);
    ms(id, 4, str);
	return 1;
}

CMD:setarsede(playerid, params[])
{
	new inter, id;
	new str[150];
	if(sscanf(params, "ud", id, inter)) return ms(playerid, 2, "Use: /setarsede [ID/Nick] [ 0 - 100 ].");
	if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
	if(inter < 0 || inter > 100) return ms(playerid, 0, "Use a value from 0 to 100!");
	pInfo[id][pSede] = (inter*2);
	format(str, 150, "You set the Thirst of '%s' to [%d].", Nome(id), inter);
    ms(playerid, 4, str);
    format(str, 150, "Admin '%s' set your Thirst to [%d].", Nome(playerid), inter);
    ms(id, 4, str);
	return 1;
}

CMD:setarcolete(playerid, params[])
{
	new inter, id;
	new str[150];
	if(sscanf(params, "ud", id, inter)) return ms(playerid, 2, "Use: /setarcolete [ID/Nick] [ 0 - 3 ].");
	if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
	if(inter < 0 || inter > 3) return ms(playerid, 0, "Use a value from 0 to 3!");
	Setar_Colete(id, inter, 100);
	format(str, 150, "You set the Vest of '%s' to [%d].", Nome(id), inter);
    ms(playerid, 4, str);
    format(str, 150, "Admin '%s' set your Vest to [%d].", Nome(playerid), inter);
    ms(id, 4, str);
	return 1;
}



CMD:setarvida(playerid, params[])
{
	new inter, id;
	new str[150];
	if(sscanf(params, "ud", id, inter)) return ms(playerid, 2, "Use: /setarvida [ID/Nick] [ 0 - 100 ].");
	if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
	if(inter < 1 || inter > 100) return ms(playerid, 0, "Use a value from 1 to 100!");
	SetarVida(id, inter);
	format(str, 150, "You set the Health of '%s' to [%d].", Nome(id), inter);
    ms(playerid, 4, str);
    format(str, 150, "Admin '%s' set your Health to [%d].", Nome(playerid), inter);
    ms(id, 4, str);
	return 1;
}

CMD:setarmascara(playerid, params[])
{
	new inter, id;
	new str[150];
	if(sscanf(params, "ud", id, inter)) return ms(playerid, 2, "Use: /setarmascara [ID/Nick] [ 0 - 100 ].");
	if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
	if(inter < 0 || inter > 100) return ms(playerid, 0, "Use a value from 0 to 100!");
	Setar_Mascara(id, inter);
	format(str, 150, "You set the Mask of '%s' to [%d].", Nome(id), inter);
    ms(playerid, 4, str);
    format(str, 150, "Admin '%s' set your Mask to [%d].", Nome(playerid), inter);
    ms(id, 4, str);
	return 1;
}

CMD:setarcapacete(playerid, params[])
{
	new inter, id;
	new str[150];
	if(sscanf(params, "ud", id, inter)) return ms(playerid, 2, "Use: /setarcapacete [ID/Nick] [ 0 - 3 ].");
	if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
	if(inter < 0 || inter > 3) return ms(playerid, 0, "Use a value from 0 to 3!");
	Setar_Capacete(id, inter, 100);
	format(str, 150, "You set the Helmet of '%s' to [%d].", Nome(id), inter);
    ms(playerid, 4, str);
    format(str, 150, "Admin '%s' set your Helmet to [%d].", Nome(playerid), inter);
    ms(id, 4, str);
	return 1;
}


CMD:setarsono(playerid, params[])
{
	new inter, id;
	new str[150];
	if(sscanf(params, "ud", id, inter)) return ms(playerid, 2, "Use: /setarsono [ID/Nick] [ 0 - 100 ].");
	if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
	if(inter < 0 || inter > 100) return ms(playerid, 0, "Use a value from 0 to 100!");
	pInfo[id][pSono] = inter;
	format(str, 150, "You set the Sleep of '%s' to [%d].", Nome(id), inter);
    ms(playerid, 4, str);
    format(str, 150, "Admin '%s' set your Sleep to [%d].", Nome(playerid), inter);
    ms(id, 4, str);
	return 1;
}

CMD:setarfrio(playerid, params[])
{
	new inter, id;
	new str[150];
	if(sscanf(params, "ud", id, inter)) return ms(playerid, 2, "Use: /setarfrio [ID/Nick] [ 0 - 100 ].");
	if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
	if(inter < 0 || inter > 100) return ms(playerid, 0, "Use a value from 0 to 100!");
	pInfo[id][pFrio] = inter;
	format(str, 150, "You set the Cold of '%s' to [%d].", Nome(id), inter);
    ms(playerid, 4, str);
    format(str, 150, "Admin '%s' set your Cold to [%d].", Nome(playerid), inter);
    ms(id, 4, str);
	return 1;
}

CMD:setarmundo(playerid, params[])
{
	new inter, id;
	new str[150];
	if(sscanf(params, "ud", id, inter)) return ms(playerid, 2, "Use: /setarmundo [ID/Nick] [Mundo].");
	if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
	SetPlayerVirtualWorld(id, inter);
	format(str, 150, "You set the World of '%s' to [%d].", Nome(id), inter);
    ms(playerid, 4, str);
    format(str, 150, "Admin '%s' set your World to [%d].", Nome(playerid), inter);
    ms(id, 4, str);
	return 1;
}

CMD:setarinterior(playerid, params[])
{
	new inter, id;
	new str[150];
	if(sscanf(params, "ud", id, inter)) return ms(playerid, 2, "Use: /setarinterior [ID/Nick] [Interior].");
	if(!Online(id)) return ms(playerid, 0, "This player is not Online!");
	SetPlayerInterior(id, inter);
	format(str, 150, "You set the Interior of '%s' to [%d].", Nome(id), inter);
    ms(playerid, 4, str);
    format(str, 150, "Admin '%s' set your Interior to [%d].", Nome(playerid), inter);
    ms(id, 4, str);
	return 1;
}

CMD:setaradmin(playerid, params[])
{
	new level, id, funcao[75];
	new sss[150];
	if(sscanf(params, "uds[75]", id, level, funcao)) return ms(playerid, 2, "Use: /setaradmin [ ID/Nick ] [ level ] [ funcao ].");
	// defense-in-depth: ensure caller has sufficient admin level
	if(AdminPlayer(playerid) < 6) return ms(playerid, 0, "You do not have permission to use this command.");
	if(!Online(id)) return ms(playerid, 0, "The player is not Online!");
	if(level < 1 || level > 5) return ms(playerid, 0, "Use um level entre 1 e 5 !");
	if(!AdminPlayer(id)) return ms(playerid, 0, "The player is not an admin, use /daradmin to do that!");

    for(new i; i<MAX_ADMINS; i++)
	{
		if(Admin[i][adm_Existe] == 1)
		{
			if(Comparar(Admin[i][adm_Nome], Nome(id)))
			{
				Admin[i][adm_Level] = level;
				format(Admin[i][adm_Funcao], 40, funcao);
				format(Admin[i][adm_Responssavel], MAX_PLAYER_NAME, Nome(playerid));
				format(sss, 150, "The admin '%s' set your admin level %d: %s.", Nome(playerid), level, funcao);
				ms(id, 4, sss);
				format(sss, 150, "You set '%s' as admin level %d: %s.", Nome(id), level, funcao);
				ms(playerid, 4, sss);
				format(sss, 150, "The Admin '%s' set '%s' as level %d, function '%s'.", Nome(playerid), Nome(id), level, funcao);
				escrever_log_admin(sss);
				salvar_admin(i);
				return 1;
			}
		}
	}
	return 1;
}

CMD:daradmin(playerid, params[])
{
	new level, id, funcao[75];
	new sss[150];
	if(sscanf(params, "uds[75]", id, level, funcao)) return ms(playerid, 2, "Use: /daradmin [ ID/Nick ] [ level ] [ funcao ].");
	if(!Online(id)) return ms(playerid, 0, "The player is not Online!");
	if(level < 1 || level > 5) return ms(playerid, 0, "Use a level between 1 and 5!");
	// require caller to be high-level admin
	if(AdminPlayer(playerid) < 6) return ms(playerid, 0, "You do not have permission to use this command.");
	if(AdminPlayer(id)) return ms(playerid, 0, "The player is already admin, use /setaradmin to change the level or function!");
	if(criar_admin(Nome(id), Nome(playerid), level, funcao))
    {
        format(sss, 150, "The admin '%s' gave you admin level %d: %s.", Nome(playerid), level, funcao);
        ms(id, 4, sss);
        format(sss, 150, "You gave '%s' admin level %d: %s.", Nome(id), level, funcao);
        ms(playerid, 4, sss);
        format(sss, 150, "The Admin '%s' removed '%s' from the Administrators list.", Nome(playerid), Nome(id));
		escrever_log_admin(sss);
    }
    else ms(playerid, 0, "The admin list is full.");
	return 1;
}

CMD:removeradmin(playerid, params[])
{
	new admin[MAX_PLAYER_NAME];
	new str[150];
	if(sscanf(params, "s[150]", admin)) return ms(playerid, 2, "Use: /removeradmin [Nick].");
	// require caller to be high-level admin
	if(AdminPlayer(playerid) < 6) return ms(playerid, 0, "You do not have permission to use this command.");
	new ida = AdminID(playerid);
	new idaa = AdminIDNick(admin);
	if(idaa == -1) return ms(playerid, 0, "Administrator not found in database.");
	if(Admin[idaa][adm_Level] > Admin[ida][adm_Level]) return ms(playerid, 0, "You cannot remove a higher rank!");

	if(destruir_admin(admin))
	{
		format(str, 150, "You removed '%s' from the Administrators list.", admin);
		ms(playerid, 4, str);
		format(str, 150, "The Admin '%s' removed '%s' from the Administrators list.", Nome(playerid), admin);
		escrever_log_admin(str);
	}
	else
	{
        ms(playerid, 0, "Administrador nao encontrado no Banco de Dados.");
	}
	return 1;
}

CMD:jetpack(playerid, params[])
{
	
    if(Modo[playerid] == 1)
    {
        if(Haid() && ModoAdmin[playerid] == 0) return ms(playerid, 0, "You cannot use this item during Haid time.");
        if(GetPlayerInterior(playerid) != 0) return ms(playerid, 0, "You cannot use this item inside an interior!");
        if(!tem_jetpack(playerid)) return ms(playerid, 0, "You don't have a JetPack in your inventory.");
        if(EmCombate(playerid)) return ms(playerid, 0, "You cannot use JetPack while fighting.");
        if(JetPack[playerid] < 50) return ms(playerid, 0, "Your JetPack battery is almost empty, wait a moment and try again.");
        if(invaberto[playerid] == 1) fecharinv(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
        format(string_prox, 300, " Player %s took their JetPack ", Nome(playerid));
        ProxDetector(20.0, playerid, string_prox, 0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA,0xBCA9F5AA);
    }
    return 1;
}



CMD:cameras(playerid, params[])
{
    if(tv_player[playerid] != -1) return ms(playerid, 0, "You cannot do this in /tv mode!");
    if(IsPlayerInAnyVehicle(playerid))return ms(playerid, 0, "You cannot do this in a vehicle!");
	if(cadeira_player[playerid] != -1)return ms(playerid, 0, "You cannot do this while sitting!");
	if(cama_player[playerid] != -1)return ms(playerid, 0, "You cannot do that lying in bed!");
	if(Barra[playerid][b_Acao] != 0)return ms(playerid, 0, "You cannot do this at this moment!");
	if(Morto[playerid] != 0) return ms(playerid, 0, "You cannot do this right now!");
	if(com_jetpack[playerid] == 1)return ms(playerid, 0, "You cannot do this in a Jetpack, exit it first!");
    if(EmCombate(playerid)) return ms(playerid, 0, "You cannot view cameras while in combat.");
    MostrarCameras( playerid, 0, -1);
	return 1;
}

CMD:destruirpedra(playerid, params[])
{
    for(new i; i<MAX_PEDRAS; i++)
	{
		if(Pedra[i][ar_Existe] == 1)
		{
		    if(IsPlayerInRangeOfPoint(playerid, 5, Pedra[i][ar_X], Pedra[i][ar_Y], Pedra[i][ar_Z]))
		    {
		        if(GetPlayerInterior(playerid) == Pedra[i][ar_Interior] && GetPlayerVirtualWorld(playerid) == Pedra[i][ar_Mundo])
		        {
		            SetPVarInt(playerid, "id_pedra", i);
		            ShowPlayerDialog_(playerid, DIALOG_DESTRUIR_PEDRA, 0, "{000000}_", "\n{ff0000}ATENCAO {ffffff}Deseja realmente dewstruir esta Pedra ?\n", "Sim", "Cancelar");
		        }
		    }
		}
	}

	return 1;
}



CMD:editarpedra(playerid, params[])
{
    for(new i; i<MAX_PEDRAS; i++)
	{
		if(Pedra[i][ar_Existe] == 1)
		{
		    if(IsPlayerInRangeOfPoint(playerid, 5, Pedra[i][ar_X], Pedra[i][ar_Y], Pedra[i][ar_Z]))
		    {
		        if(GetPlayerInterior(playerid) == Pedra[i][ar_Interior] && GetPlayerVirtualWorld(playerid) == Pedra[i][ar_Mundo])
		        {
		            EditDynamicObject2(playerid, Pedra[i][ar_Obj],  747);
		        }
		    }
		}
	}
	return 1;
}

CMD:editararvore(playerid, params[])
{
    for(new i; i<MAX_ARVORES; i++)
	{
		if(Arvore[i][ar_Existe] == 1)
		{
		    if(IsPlayerInRangeOfPoint(playerid, 5, Arvore[i][ar_X], Arvore[i][ar_Y], Arvore[i][ar_Z]))
		    {
		        if(GetPlayerInterior(playerid) == Arvore[i][ar_Interior] && GetPlayerVirtualWorld(playerid) == Arvore[i][ar_Mundo])
		        {
		            EditDynamicObject2(playerid, Arvore[i][ar_Obj],  657);
		        }
		    }
		}
	}
	return 1;
}

CMD:criarpedra(playerid, params[])
{
    new Float:pos[4];
	GetPlayerPos(playerid, pos[0],pos[1],pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);
	new ar = CriarPedra(pos[0],pos[1],pos[2], pos[3], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	Streamer_Update(playerid);
	EditDynamicObject2(playerid, Pedra[ar][ar_Obj],  747);

	PegarFrentePlayer(playerid, pos[0],pos[1], -1);
	SetPlayerPos(playerid, pos[0],pos[1],pos[2]);
	return 1;
}

CMD:criararvore(playerid, params[])
{
    new Float:pos[4];
	GetPlayerPos(playerid, pos[0],pos[1],pos[2]);
	GetPlayerFacingAngle(playerid, pos[3]);
	new ar = CriarArvore(pos[0],pos[1],pos[2], pos[3], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	Streamer_Update(playerid);
	EditDynamicObject2(playerid, Arvore[ar][ar_Obj],  657);

	PegarFrentePlayer(playerid, pos[0],pos[1], -1);
	SetPlayerPos(playerid, pos[0],pos[1],pos[2]);
	return 1;
}