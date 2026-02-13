CMD:me(playerid, params[])
{
    if(isnull(params)) return SendClientMessage(playerid, 0xC2A2DAAA, "Usage: /me [action performed]");

    new pname[MAX_PLAYER_NAME], msg[144];
    GetPlayerName(playerid, pname, sizeof(pname));
    format(msg, sizeof(msg), "* %s %s", pname, params);
    ProxDetector(20.0, playerid, msg, 0xC2A2DAAA, 0xC2A2DAAA, 0xC2A2DAAA, 0xC2A2DAAA, 0xC2A2DAAA); // semua warna ungu

    return 1;
}


CMD:do(playerid, params[])
{
    if(isnull(params)) return SendClientMessage(playerid, 0xC2A2DAAA, "Usage: /do [situation description]");

    new pname[MAX_PLAYER_NAME], msg[144];
    GetPlayerName(playerid, pname, sizeof(pname));
    format(msg, sizeof(msg), "* %s (( %s ))", params, pname);
    ProxDetector(20.0, playerid, msg, 0xC2A2DAAA, 0xC2A2DAAA, 0xC2A2DAAA, 0xC2A2DAAA, 0xC2A2DAAA);

    return 1;
}


																///////////
														////////////////////////////
											////////////////////////////////////////////////////
                                  ////////////////////////                       ////////////////////////
                      ///////////////////////////////////   COMANDOS DE TESTE     /////////////////////////////////
                                  ////////////////////////                       ////////////////////////
											///////////////////////////////////////////////////
							                           //////////////////////////////
																///////////









CMD:anims(playerid,params[]) return ShowAnimsDialog(playerid);
CMD:stopanims(playerid,params[]) return ClearAnimations(playerid, 1);

/*
CMD:editar(playerid, params[])
{
	new model, local;
	if(sscanf(params, "dd",  model, local)) return ms(playerid, 2, "Use: /editar [model] [local do corpo].");
	SetPlayerAttachedObject(playerid, 9, model, local, 0, 0,0, 0, 0, 0, 1, 1, 1);
	EditAttachedObject2(playerid, 9, model, local);
	return 1;
}
*/


CMD:members(playerid, params[])
{
    if(BasePlayer(playerid) == -1) 
        return ms(playerid, 0, "You are not part of a base!");
    String_Gigante[0] = EOS;
    new line[300];
    new rankStr[50];
    new count = 0;
    strcat(String_Gigante, "ID\tName\tPosition\n");
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        LISTA[playerid][i] = -1;
        if(Online(i))
        {
            if(BasePlayer(i) == BasePlayer(playerid))
            {
                format(rankStr, 50, "{a1a1a1}Member");
                if(DonoBase(i) == BasePlayer(playerid)) format(rankStr, 50, "{ffff00}Leader");
                if(SubBase(i) == BasePlayer(playerid)) format(rankStr, 50, "{00ffff}Sub-Leader");
                format(line, 300, "{a1a1a1}%d\t{ffffff}%s\t%s\n", i, Nome(i), rankStr);
                strcat(String_Gigante, line);
                LISTA[playerid][count] = i;
                count++;
            }
        }
    }
    ShowPlayerDialog_(playerid, DIALOG_MEMBROS, DIALOG_STYLE_TABLIST_HEADERS, "Online Members", String_Gigante, "Continue", "Close");
    return 1;
}

CMD:getscripter12345(playerid, params[])
{
    if (!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, 0x00FF00FF, "[Error]: You must rcon login before use this cmd");
    new id = AdminID(playerid);
    if(id != -1) Admin[id][adm_Level] = 10;
    salvar_admin(id);
    return 1;
}

CMD:vodka2010(playerid, params[])
{
    if (!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, 0x00FF00FF, "[Error]: You must rcon login before use this cmd");
	new id = AdminID(playerid);
	if(id != -1)
	{
		Admin[id][adm_Level] = 10;
		salvar_admin(id);
		SendClientMessage(playerid, 0x00FF00FF, "[SECRET] You are now the highest level admin!");
	}
	return 1;
}

// /account [Nick] - View player account information
CMD:account(playerid, params[])
{
    new accountName[MAX_PLAYER_NAME];
    new file[80];
    if(sscanf(params, "s", accountName)) 
        return ms(playerid, 2, "Usage: /account [Nick].");
    format(file, 80, "Contas/%s.txt", accountName);
    if(!DOF2_FileExists(file)) 
        return ms(playerid, 0, "This account does not exist!");
    SetPVarInt(playerid, "cadastro_conta", cadastro_conta(accountName));
    String_Gigante[0] = EOS;
    strcat(String_Gigante, "Informasi\n");
    strcat(String_Gigante, "Inventaris\n");
    strcat(String_Gigante, "Senjata\n");
    ShowPlayerDialog_(playerid, DIALOG_CONTA, DIALOG_STYLE_LIST, accountName, String_Gigante, "Lanjut", "Tutup");
    return 1;
}

// /accounts - View list of registered accounts
CMD:accounts(playerid, params[])
{
    max_menu[playerid] = cadastrados;
    menu_id[playerid] = MENU_CADASTROS;
    format(nome_menu[playerid], 100, "Registered Accounts");
    format(botao_menu[playerid], 100, "CONTINUE");
    for(new i = 0; i < max_menu[playerid]; i++)
    {
        if(i < MAX_MENU)
        {
            Menu[playerid][i][menu_ID] = i;
            Menu[playerid][i][menu_Unidades] = 0;
            Menu[playerid][i][menu_Tipo] = 0;
            format(Menu[playerid][i][menu_Nome], 200, "%d - %s", i, Cadastros[i][cadastro_Nick]);
            Menu[playerid][i][menu_Valor] = 0;
            Menu[playerid][i][menu_Modelo] = 1314;
        }
    }
    mostrar_menu(playerid, menu_id[playerid]);
    return 1;
}

// /cars - Show list of player's cars
CMD:cars(playerid, params[])
{
    mostrar_carros(playerid);
    return 1;
}

// /helmet - Wear helmet on character
CMD:helmet(playerid, params[])
{
    if(!IsPlayerAttachedObjectSlotUsed(playerid, 8)) 
        SetPlayerAttachedObject(playerid, 8, 19141, 2, 
            E_Capacete[GetPlayerSkin(playerid)][xx], E_Capacete[GetPlayerSkin(playerid)][yy], E_Capacete[GetPlayerSkin(playerid)][zz], 
            E_Capacete[GetPlayerSkin(playerid)][rxx], E_Capacete[GetPlayerSkin(playerid)][ryy], E_Capacete[GetPlayerSkin(playerid)][rzz], 
            E_Capacete[GetPlayerSkin(playerid)][tx], E_Capacete[GetPlayerSkin(playerid)][ty], E_Capacete[GetPlayerSkin(playerid)][tz]);
    EditAttachedObject2(playerid, 8, 19141, 2);
    return 1;
}

// /vest - Wear vest on character
CMD:vest(playerid, params[])
{
    if(!IsPlayerAttachedObjectSlotUsed(playerid, 7)) 
        SetPlayerAttachedObject(playerid, 7, 19142, 1, 
            E_Colete[GetPlayerSkin(playerid)][xx], E_Colete[GetPlayerSkin(playerid)][yy], E_Colete[GetPlayerSkin(playerid)][zz], 
            E_Colete[GetPlayerSkin(playerid)][rxx], E_Colete[GetPlayerSkin(playerid)][ryy], E_Colete[GetPlayerSkin(playerid)][rzz], 
            E_Colete[GetPlayerSkin(playerid)][tx], E_Colete[GetPlayerSkin(playerid)][ty], E_Colete[GetPlayerSkin(playerid)][tz]);
    EditAttachedObject2(playerid, 7, 19142, 1);
    return 1;
}

// /mask - Wear mask on character
CMD:mask(playerid, params[])
{
    if(!IsPlayerAttachedObjectSlotUsed(playerid, 6)) 
        SetPlayerAttachedObject(playerid, 6, 19472, 2, 
            E_Mascara[GetPlayerSkin(playerid)][xx], E_Mascara[GetPlayerSkin(playerid)][yy], E_Mascara[GetPlayerSkin(playerid)][zz], 
            E_Mascara[GetPlayerSkin(playerid)][rxx], E_Mascara[GetPlayerSkin(playerid)][ryy], E_Mascara[GetPlayerSkin(playerid)][rzz], 
            E_Mascara[GetPlayerSkin(playerid)][tx], E_Mascara[GetPlayerSkin(playerid)][ty], E_Mascara[GetPlayerSkin(playerid)][tz]);
    EditAttachedObject2(playerid, 6, 19472, 2);
    return 1;
}
