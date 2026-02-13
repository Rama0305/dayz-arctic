#include <a_samp>
#include <streamer>

// editar no android //
enum edii
{
	Float:Edit_X,
	Float:Edit_Y,
	Float:Edit_Z,
	Float:Edit_RX,
	Float:Edit_RY,
	Float:Edit_RZ,
	Float:Edit_TX,
	Float:Edit_TY,
	Float:Edit_TZ,
	Edit_Tipo,
	Edit_Index,
	Edit_Bone,
 	Edit_Modelo
};
new Editado[MAX_PLAYERS][10][edii];
new Edit[MAX_PLAYERS][edii];
new editando[MAX_PLAYERS];
new Float:pixel[MAX_PLAYERS];
new Text:InvEditar[10];
new PlayerText:InvEditar_p[MAX_PLAYERS][1];
new Text:T_Editar[8];
new PlayerText:T_Editar_p[MAX_PLAYERS][1];
new movendo_camera[MAX_PLAYERS];


CMD:movercamera(playerid, params[])
{
	if(GetPVarInt(playerid, "Android") == 1)
	{
	    if(editando[playerid] != 0)
	    {
			if(movendo_camera[playerid] == 0)
			{
			    CancelSelectTextDraw(playerid);
			    movendo_camera[playerid] = 1;
                GameTextForPlayer(playerid, "~w~APERTE ~Y~F ~W~PARA~N~VOLTAR A EDITAR", 180000, 3);
			}
			else if(movendo_camera[playerid] == 1)
			{

			    SelectTextDraw(playerid, 0x00ffffff);
			    movendo_camera[playerid] = 0;
			    GameTextForPlayer(playerid, "~y~VOCE VOLTOU A EDITAR", 1500, 3);
			}
	    }
 	}
	return 1;
}


/*

native EditAttachedObject2(playerid, index, model=0, bone=0);
native EditDynamicObject2(playerid, obj, model );

*/

forward EditAttachedObject2(playerid, index, model, bone);
public EditAttachedObject2(playerid, index, model, bone)
{
	if(GetPVarInt(playerid, "Android") == 1)
	{
	    Edit[playerid][Edit_Tipo] = 1;
	    Edit[playerid][Edit_Modelo] = Editado[playerid][index][Edit_Modelo];
	    Edit[playerid][Edit_Index] = Editado[playerid][index][Edit_Index];
	    Edit[playerid][Edit_Bone] = Editado[playerid][index][Edit_Bone];
	    Edit[playerid][Edit_X] = Editado[playerid][index][Edit_X];
	    Edit[playerid][Edit_Y] = Editado[playerid][index][Edit_Y];
	    Edit[playerid][Edit_Z] = Editado[playerid][index][Edit_Z];
	    Edit[playerid][Edit_RX] = Editado[playerid][index][Edit_RX];
	    Edit[playerid][Edit_RY] = Editado[playerid][index][Edit_RY];
	    Edit[playerid][Edit_RZ] = Editado[playerid][index][Edit_RZ];
	    Edit[playerid][Edit_TX] = Editado[playerid][index][Edit_TX];
	    Edit[playerid][Edit_TY] = Editado[playerid][index][Edit_TY];
	    Edit[playerid][Edit_TZ] = Editado[playerid][index][Edit_TZ];
		pixel[playerid] = 0.010;
	    SetTimerEx("Editar", 1000, 0, "dd",  playerid, 0);
	    return 1;
	}
	EditAttachedObject(playerid, index);
	return 1;
}

forward editar__(playerid, obj);
public editar__(playerid, obj)
{
    EditDynamicObject(playerid, obj);
	return 1;
}

stock EditDynamicObject2(playerid, obj, model=0 )
{
	Streamer_Update(playerid);
	if(GetPVarInt(playerid, "Android") == 1)
	{
	    Edit[playerid][Edit_Tipo] = 0;
	    Edit[playerid][Edit_Index] = obj;
	    Edit[playerid][Edit_Modelo] = model;
	    pixel[playerid] = 0.010;
		GetDynamicObjectPos(obj, Edit[playerid][Edit_X], Edit[playerid][Edit_Y], Edit[playerid][Edit_Z] );
		GetDynamicObjectRot(obj, Edit[playerid][Edit_RX], Edit[playerid][Edit_RY], Edit[playerid][Edit_RZ] );
	    SetTimerEx("Editar", 1000, 0, "dd",  playerid, 0);
 		return 1;
	}
	SetTimerEx("editar__", 1000, 0, "dd", playerid, obj);
	return 1;
}

forward Editar(playerid, con);
public Editar(playerid, con)
{
	if(con == 0)
	{
		if(editando[playerid] == 0)
		{
		    for(new i; i<sizeof InvEditar; i++) TextDrawShowForPlayer(playerid, InvEditar[i]);
		    for(new ii; ii<sizeof T_Editar; ii++) TextDrawShowForPlayer(playerid, T_Editar[ii]);
			PlayerTextDrawShow(playerid, InvEditar_p[playerid][0]);
			PlayerTextDrawShow(playerid, T_Editar_p[playerid][0]);
			editando[playerid] = 1;
			SelectTextDraw(playerid, 0x00ffffff);
		}

		if(editando[playerid] == 1) PlayerTextDrawSetString(playerid, InvEditar_p[playerid][0], "POSICAO");
		if(editando[playerid] == 2) PlayerTextDrawSetString(playerid, InvEditar_p[playerid][0], "ROTACAO");
		if(editando[playerid] == 3) PlayerTextDrawSetString(playerid, InvEditar_p[playerid][0], "TAMANHO");
		PlayerTextDrawShow(playerid, InvEditar_p[playerid][0]);
		if(pixel[playerid] == 0.010) PlayerTextDrawSetString(playerid, T_Editar_p[playerid][0], "_~n~~n~_~n~~n~o~n~");
		if(pixel[playerid] == 0.5) PlayerTextDrawSetString(playerid, T_Editar_p[playerid][0], "_~n~~n~o~n~~n~_~n~");
		if(pixel[playerid] == 1.5) PlayerTextDrawSetString(playerid, T_Editar_p[playerid][0], "o~n~~n~_~n~~n~_~n~");
        PlayerTextDrawShow(playerid, T_Editar_p[playerid][0]);
		return 1;
	}

	if(con == 1)
	{
        if(Edit[playerid][Edit_Tipo] == 0)
        {
            if(IsValidDynamicObject(Edit[playerid][Edit_Index]))
            {
	            SetDynamicObjectPos(Edit[playerid][Edit_Index], Edit[playerid][Edit_X], Edit[playerid][Edit_Y], Edit[playerid][Edit_Z]);
	            SetDynamicObjectRot(Edit[playerid][Edit_Index], Edit[playerid][Edit_RX], Edit[playerid][Edit_RY], Edit[playerid][Edit_RZ]);
            }
        }
        else
        {
            if(IsPlayerAttachedObjectSlotUsed(playerid, Edit[playerid][Edit_Index]))
            {
                SetPlayerAttachedObject(playerid, Edit[playerid][Edit_Index], Edit[playerid][Edit_Modelo], Edit[playerid][Edit_Bone], Edit[playerid][Edit_X], Edit[playerid][Edit_Y], Edit[playerid][Edit_Z], Edit[playerid][Edit_RX], Edit[playerid][Edit_RY], Edit[playerid][Edit_RZ], Edit[playerid][Edit_TX], Edit[playerid][Edit_TY], Edit[playerid][Edit_TZ] );
            }
        }

	    return 1;
	}

	if(con == 555) // salvou //
	{
	    if(Edit[playerid][Edit_Tipo] == 0)
	    {
            OnPlayerEditDynamicObject(playerid, Edit[playerid][Edit_Index], 1, Edit[playerid][Edit_X], Edit[playerid][Edit_Y], Edit[playerid][Edit_Z], Edit[playerid][Edit_RX], Edit[playerid][Edit_RY], Edit[playerid][Edit_RZ]);
		}
	    else
	    {
	        OnPlayerEditAttachedObject(playerid, 1, Edit[playerid][Edit_Index], Edit[playerid][Edit_Modelo], Edit[playerid][Edit_Bone], Edit[playerid][Edit_X], Edit[playerid][Edit_Y], Edit[playerid][Edit_Z], Edit[playerid][Edit_RX], Edit[playerid][Edit_RY], Edit[playerid][Edit_RZ], Edit[playerid][Edit_TX], Edit[playerid][Edit_TY], Edit[playerid][Edit_TZ]);
	    }

	    for(new i; i<sizeof InvEditar; i++) TextDrawHideForPlayer(playerid, InvEditar[i]);
	    for(new ii; ii<sizeof T_Editar; ii++) TextDrawHideForPlayer(playerid, T_Editar[ii]);
	    PlayerTextDrawHide(playerid, InvEditar_p[playerid][0]);
	    PlayerTextDrawHide(playerid, T_Editar_p[playerid][0]);
		CancelSelectTextDraw(playerid);
		editando[playerid] = 0;
		GameTextForPlayer(playerid, "~W~EDICAO ~G~CONCLUIDA", 1500, 3);
		return 1;
	}

	if(con == 666) // cancelou //
	{
	    if(Edit[playerid][Edit_Tipo] == 0)
	    {
            OnPlayerEditDynamicObject(playerid, Edit[playerid][Edit_Index], 0, Edit[playerid][Edit_X], Edit[playerid][Edit_Y], Edit[playerid][Edit_Z], Edit[playerid][Edit_RX], Edit[playerid][Edit_RY], Edit[playerid][Edit_RZ]);
	    }
	    else
	    {
	        OnPlayerEditAttachedObject(playerid, 1, Edit[playerid][Edit_Index], Edit[playerid][Edit_Modelo], Edit[playerid][Edit_Bone], Edit[playerid][Edit_X], Edit[playerid][Edit_Y], Edit[playerid][Edit_Z], Edit[playerid][Edit_RX], Edit[playerid][Edit_RY], Edit[playerid][Edit_RZ], Edit[playerid][Edit_TX], Edit[playerid][Edit_TY], Edit[playerid][Edit_TZ]);
	    }

	    for(new i; i<sizeof InvEditar; i++) TextDrawHideForPlayer(playerid, InvEditar[i]);
	    for(new ii; ii<sizeof T_Editar; ii++) TextDrawHideForPlayer(playerid, T_Editar[ii]);
	    PlayerTextDrawHide(playerid, InvEditar_p[playerid][0]);
	    PlayerTextDrawHide(playerid, T_Editar_p[playerid][0]);
        CancelSelectTextDraw(playerid);
        editando[playerid] = 0;
        GameTextForPlayer(playerid, "~W~EDICAO ~R~CANCELADA", 1500, 3);
		return 1;
	}

	return 1;
}

public OnPlayerClickTextDraw( playerid, Text:clickedid )
{

	if(clickedid == Text:INVALID_TEXT_DRAW)
	{
	    if(editando[playerid] != 0)
	    {
	        if(movendo_camera[playerid] == 0)
	        {
		        Editar(playerid, 666);
		        return 1;
	        }
	    }
	}

	// editar no android //



    if( clickedid == T_Editar[0]) //       /camera        //
	{
	    cmd_movercamera(playerid, "");
	    return 1;
	}


	if( clickedid == T_Editar[3]) //   ESCALA DE PIXEL   //
	{
	    if(pixel[playerid] == 0.010) pixel[playerid] = 0.5;
	    else if(pixel[playerid] == 0.5) pixel[playerid] = 1.5;
	    else if(pixel[playerid] == 1.5) pixel[playerid] = 0.010;
	    Editar(playerid, 0);
	    return 1;
	}


	if( clickedid == InvEditar[1]) // + x
	{
        if(editando[playerid] == 1)
    	{
            if(Edit[playerid][Edit_Tipo] == 1) Edit[playerid][Edit_X] += pixel[playerid];
            else Edit[playerid][Edit_X] += pixel[playerid]/2;
    	}
    	if(editando[playerid] == 2)
    	{
            Edit[playerid][Edit_RX] += (pixel[playerid]*5);
    	}
    	if(editando[playerid] == 3)
    	{
            Edit[playerid][Edit_TX] +=  pixel[playerid];
		}
        Editar(playerid, 1);
	}

	if( clickedid == InvEditar[2]) // + y
	{
        if(editando[playerid] == 1)
    	{
            if(Edit[playerid][Edit_Tipo] == 1) Edit[playerid][Edit_Y] += pixel[playerid];
            else Edit[playerid][Edit_Y] += pixel[playerid]/2;
    	}

    	if(editando[playerid] == 2)
    	{
            Edit[playerid][Edit_RY] += (pixel[playerid]*5);
    	}

    	if(editando[playerid] == 3)
    	{
            Edit[playerid][Edit_TY] +=  pixel[playerid];
		}

        Editar(playerid, 1);
	}

	if( clickedid == InvEditar[3]) // + z
	{
        if(editando[playerid] == 1)
    	{
    	    if(Edit[playerid][Edit_Tipo] == 1) Edit[playerid][Edit_Z] += pixel[playerid];
            else Edit[playerid][Edit_Z] += pixel[playerid]/2;
    	}

    	if(editando[playerid] == 2)
    	{
            Edit[playerid][Edit_RZ] += (pixel[playerid]*5);
    	}

    	if(editando[playerid] == 3)
    	{
            Edit[playerid][Edit_TZ] +=  pixel[playerid];
		}

        Editar(playerid, 1);
	}

	if( clickedid == InvEditar[4]) // - x
	{
        if(editando[playerid] == 1)
    	{
            if(Edit[playerid][Edit_Tipo] == 1) Edit[playerid][Edit_X] -= pixel[playerid];
            else Edit[playerid][Edit_X] -= pixel[playerid]/2;
    	}

    	if(editando[playerid] == 2)
    	{
            Edit[playerid][Edit_RX] -= (pixel[playerid]*5);
    	}

    	if(editando[playerid] == 3)
    	{
            Edit[playerid][Edit_TX] -=  pixel[playerid];
		}

        Editar(playerid, 1);
	}

	if( clickedid == InvEditar[5]) // - y
	{
        if(editando[playerid] == 1)
    	{
            if(Edit[playerid][Edit_Tipo] == 1) Edit[playerid][Edit_Y] -= pixel[playerid];
            else Edit[playerid][Edit_Y] -= pixel[playerid]/2;
    	}

    	if(editando[playerid] == 2)
    	{
            Edit[playerid][Edit_RY] -= (pixel[playerid]*5);
    	}

    	if(editando[playerid] == 3)
    	{
            Edit[playerid][Edit_TY] -=  pixel[playerid];
		}

        Editar(playerid, 1);
	}


	if( clickedid == InvEditar[6]) // - z
	{
        if(editando[playerid] == 1)
    	{
            if(Edit[playerid][Edit_Tipo] == 1) Edit[playerid][Edit_Z] -= pixel[playerid];
            else Edit[playerid][Edit_Z] -= pixel[playerid]/2;
    	}

    	if(editando[playerid] == 2)
    	{
            Edit[playerid][Edit_RZ] -= (pixel[playerid]*5);
    	}

    	if(editando[playerid] == 3)
    	{
            Edit[playerid][Edit_TZ] -= pixel[playerid];
		}

        Editar(playerid, 1);
	}

	if( clickedid == InvEditar[7])
	{
     	Editar(playerid, 555);
	}

	if( clickedid == InvEditar[8])
	{
 		Editar(playerid, 666);
	}

	if( clickedid == InvEditar[9])
	{
	    if(editando[playerid] != 0)
	    {
	        if(Edit[playerid][Edit_Tipo] == 0)
	        {
	            if(editando[playerid] == 1) editando[playerid] = 2;
	            else editando[playerid] = 1;

	        }
	        else
	        {
	            if(editando[playerid] == 1) editando[playerid] = 2;
	            else if(editando[playerid] == 2) editando[playerid] = 3;
	            else editando[playerid] = 1;
	        }
	        Editar(playerid, 0);
	    }
		return 1;
	}

	#if defined NA_OnPlayerClickTextDraw
		return NA_OnPlayerClickTextDraw(playerid, Text:clickedid);
	#else
		return 0;
	#endif
}

public OnPlayerDeath(playerid, killerid, reason)
{

    if(editando[playerid] != 0)
    {
        Editar(playerid, 666);
    }

    #if defined NA_OnPlayerDeath
		return NA_OnPlayerDeath(playerid, killerid, reason);
	#else
		return 0;
	#endif
}

public OnPlayerSpawn(playerid)
{
    if(editando[playerid] != 0)
    {
        Editar(playerid, 666);
    }

    #if defined NA_OnPlayerSpawn
		return NA_OnPlayerSpawn(playerid);
	#else
		return 0;
	#endif
}

public OnPlayerDisconnect(playerid, reason)
{
    if(editando[playerid] != 0)
    {
        Editar(playerid, 666);
    }

    #if defined NE_OnPlayerDisconnect
		return NE_OnPlayerDisconnect(playerid, reason);
	#else
		return 0;
	#endif
}

public OnPlayerConnect(playerid)
{

    editando[playerid] = 0;
    movendo_camera[playerid] = 0;

    // editar no android //

	T_Editar_p[playerid][0] = CreatePlayerTextDraw(playerid, 592.800048, 262.411285, "o~n~~n~o~n~~n~o");
	PlayerTextDrawLetterSize(playerid, T_Editar_p[playerid][0], 0.356500, 1.489111);
	PlayerTextDrawAlignment(playerid, T_Editar_p[playerid][0], 1);
	PlayerTextDrawColor(playerid, T_Editar_p[playerid][0], 16777182);
	PlayerTextDrawSetShadow(playerid, T_Editar_p[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, T_Editar_p[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, T_Editar_p[playerid][0], 109);
	PlayerTextDrawFont(playerid, T_Editar_p[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, T_Editar_p[playerid][0], 1);

	InvEditar_p[playerid][0] = CreatePlayerTextDraw(playerid, 448.375091, 368.133544, "POSICAO");
	PlayerTextDrawLetterSize(playerid, InvEditar_p[playerid][0], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, InvEditar_p[playerid][0], 546.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, InvEditar_p[playerid][0], 1);
	PlayerTextDrawColor(playerid, InvEditar_p[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, InvEditar_p[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, InvEditar_p[playerid][0], 255);
	PlayerTextDrawFont(playerid, InvEditar_p[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, InvEditar_p[playerid][0], 1);

    #if defined NA_OnPlayerConnect
		return NA_OnPlayerConnect(playerid);
	#else
		return 0;
	#endif
}

stock Editar_TextDraws()
{

    // sistema de editar no android //
    T_Editar[0] = TextDrawCreate(531.499755, 339.633361, "box");
	TextDrawLetterSize(T_Editar[0], 0.000000, 7.698997);
	TextDrawTextSize(T_Editar[0], 631.000000, 70.000000);
	TextDrawAlignment(T_Editar[0], 1);
	TextDrawColor(T_Editar[0], -1);
	TextDrawUseBox(T_Editar[0], 1);
	TextDrawBoxColor(T_Editar[0], 1716060328);
	TextDrawSetShadow(T_Editar[0], 0);
	TextDrawBackgroundColor(T_Editar[0], 255);
	TextDrawFont(T_Editar[0], 1);
	TextDrawSetProportional(T_Editar[0], 1);
	TextDrawSetSelectable(T_Editar[0], true);

	T_Editar[1] = TextDrawCreate(453.200042, 297.666778, "");
	TextDrawTextSize(T_Editar[1], 155.000000, 155.000000);
	TextDrawAlignment(T_Editar[1], 1);
	TextDrawColor(T_Editar[1], -47);
	TextDrawSetShadow(T_Editar[1], 0);
	TextDrawFont(T_Editar[1], 5);
	TextDrawSetProportional(T_Editar[1], 0);
	TextDrawSetPreviewModel(T_Editar[1], 367);
	TextDrawBackgroundColor(T_Editar[1], 0x00000000);
	TextDrawSetPreviewRot(T_Editar[1], 347.000000, 0.000000, 93.000000, 0.938967);

	T_Editar[2] = TextDrawCreate(624.800048, 340.777893, "mover~n~camera~n~");
	TextDrawLetterSize(T_Editar[2], 0.307999, 1.438222);
	TextDrawAlignment(T_Editar[2], 3);
	TextDrawColor(T_Editar[2], -84);
	TextDrawSetShadow(T_Editar[2], 0);
	TextDrawSetOutline(T_Editar[2], 1);
	TextDrawBackgroundColor(T_Editar[2], 40);
	TextDrawFont(T_Editar[2], 2);
	TextDrawSetProportional(T_Editar[2], 1);

	T_Editar[3] = TextDrawCreate(579.199951, 243.700210, "box");
	TextDrawLetterSize(T_Editar[3], 0.000000, 9.700001);
	TextDrawTextSize(T_Editar[3], 630.500122, 80.000000);
	TextDrawAlignment(T_Editar[3], 1);
	TextDrawColor(T_Editar[3], -1);
	TextDrawUseBox(T_Editar[3], 1);
	TextDrawBoxColor(T_Editar[3], 65362);
	TextDrawSetShadow(T_Editar[3], 0);
	TextDrawBackgroundColor(T_Editar[3], 255);
	TextDrawFont(T_Editar[3], 1);
	TextDrawSetProportional(T_Editar[3], 1);
	TextDrawSetSelectable(T_Editar[3], true);

	T_Editar[4] = TextDrawCreate(592.903076, 239.489044, "i");
	TextDrawLetterSize(T_Editar[4], 0.520500, 11.449778);
	TextDrawAlignment(T_Editar[4], 1);
	TextDrawColor(T_Editar[4], 118);
	TextDrawSetShadow(T_Editar[4], 0);
	TextDrawBackgroundColor(T_Editar[4], 255);
	TextDrawFont(T_Editar[4], 2);
	TextDrawSetProportional(T_Editar[4], 1);

	T_Editar[5] = TextDrawCreate(581.502685, 260.555511, "-~n~~n~-~n~~n~-");
	TextDrawLetterSize(T_Editar[5], 1.979999, 1.581333);
	TextDrawAlignment(T_Editar[5], 1);
	TextDrawColor(T_Editar[5], 126);
	TextDrawSetShadow(T_Editar[5], 0);
	TextDrawBackgroundColor(T_Editar[5], 255);
	TextDrawFont(T_Editar[5], 1);
	TextDrawSetProportional(T_Editar[5], 1);

	T_Editar[6] = TextDrawCreate(609.602416, 264.333251, "5.0~n~~n~2.0~n~~n~0.5");
	TextDrawLetterSize(T_Editar[6], 0.317499, 1.463111);
	TextDrawAlignment(T_Editar[6], 1);
	TextDrawColor(T_Editar[6], -130);
	TextDrawSetShadow(T_Editar[6], 0);
	TextDrawBackgroundColor(T_Editar[6], 255);
	TextDrawFont(T_Editar[6], 1);
	TextDrawSetProportional(T_Editar[6], 1);

	T_Editar[7] = TextDrawCreate(624.199707, 246.633483, "pixel");
	TextDrawLetterSize(T_Editar[7], 0.307999, 1.438222);
	TextDrawAlignment(T_Editar[7], 3);
	TextDrawColor(T_Editar[7], -84);
	TextDrawSetShadow(T_Editar[7], 0);
	TextDrawSetOutline(T_Editar[7], 1);
	TextDrawBackgroundColor(T_Editar[7], 40);
	TextDrawFont(T_Editar[7], 2);
	TextDrawSetProportional(T_Editar[7], 1);

	InvEditar[0] = TextDrawCreate(433.850311, 281.183135, "X  Y  Z");
	TextDrawLetterSize(InvEditar[0], 1.450626, 5.175827);
	TextDrawTextSize(InvEditar[0], 0.000000, 934.000000);
	TextDrawAlignment(InvEditar[0], 2);
	TextDrawColor(InvEditar[0], -100);
	TextDrawSetShadow(InvEditar[0], 0);
	TextDrawBackgroundColor(InvEditar[0], 255);
	TextDrawFont(InvEditar[0], 1);
	TextDrawSetProportional(InvEditar[0], 1);

	InvEditar[1] = TextDrawCreate(360.600036, 251.633300, "LD_BEAT:up");
	TextDrawTextSize(InvEditar[1], 29.000000, 31.000000);
	TextDrawAlignment(InvEditar[1], 1);
	TextDrawColor(InvEditar[1], -40);
	TextDrawSetShadow(InvEditar[1], 0);
	TextDrawBackgroundColor(InvEditar[1], 255);
	TextDrawFont(InvEditar[1], 4);
	TextDrawSetProportional(InvEditar[1], 0);
	TextDrawSetSelectable(InvEditar[1], true);

	InvEditar[2] = TextDrawCreate(416.649871, 252.599914, "LD_BEAT:up");
	TextDrawTextSize(InvEditar[2], 29.000000, 31.000000);
	TextDrawAlignment(InvEditar[2], 1);
	TextDrawColor(InvEditar[2], -40);
	TextDrawSetShadow(InvEditar[2], 0);
	TextDrawBackgroundColor(InvEditar[2], 255);
	TextDrawFont(InvEditar[2], 4);
	TextDrawSetProportional(InvEditar[2], 0);
	TextDrawSetSelectable(InvEditar[2], true);

	InvEditar[3] = TextDrawCreate(473.450134, 252.299896, "LD_BEAT:up");
	TextDrawTextSize(InvEditar[3], 29.000000, 31.000000);
	TextDrawAlignment(InvEditar[3], 1);
	TextDrawColor(InvEditar[3], -40);
	TextDrawSetShadow(InvEditar[3], 0);
	TextDrawBackgroundColor(InvEditar[3], 255);
	TextDrawFont(InvEditar[3], 4);
	TextDrawSetProportional(InvEditar[3], 0);
	TextDrawSetSelectable(InvEditar[3], true);

	InvEditar[4] = TextDrawCreate(361.649871, 329.816528, "LD_BEAT:down");
	TextDrawTextSize(InvEditar[4], 29.000000, 31.000000);
	TextDrawAlignment(InvEditar[4], 1);
	TextDrawColor(InvEditar[4], -40);
	TextDrawSetShadow(InvEditar[4], 0);
	TextDrawBackgroundColor(InvEditar[4], 255);
	TextDrawFont(InvEditar[4], 4);
	TextDrawSetProportional(InvEditar[4], 0);
	TextDrawSetSelectable(InvEditar[4], true);

	InvEditar[5] = TextDrawCreate(417.099517, 329.633209, "LD_BEAT:down");
	TextDrawTextSize(InvEditar[5], 29.000000, 31.000000);
	TextDrawAlignment(InvEditar[5], 1);
	TextDrawColor(InvEditar[5], -40);
	TextDrawSetShadow(InvEditar[5], 0);
	TextDrawBackgroundColor(InvEditar[5], 255);
	TextDrawFont(InvEditar[5], 4);
	TextDrawSetProportional(InvEditar[5], 0);
	TextDrawSetSelectable(InvEditar[5], true);

	InvEditar[6] = TextDrawCreate(473.774200, 328.933166, "LD_BEAT:down");
	TextDrawTextSize(InvEditar[6], 29.000000, 31.000000);
	TextDrawAlignment(InvEditar[6], 1);
	TextDrawColor(InvEditar[6], -40);
	TextDrawSetShadow(InvEditar[6], 0);
	TextDrawBackgroundColor(InvEditar[6], 255);
	TextDrawFont(InvEditar[6], 4);
	TextDrawSetProportional(InvEditar[6], 0);
	TextDrawSetSelectable(InvEditar[6], true);

	InvEditar[7] = TextDrawCreate(357.500000, 372.583282, "LD_CHAT:thumbup");
	TextDrawTextSize(InvEditar[7], 39.000000, 42.000000);
	TextDrawAlignment(InvEditar[7], 1);
	TextDrawColor(InvEditar[7], 16711855);
	TextDrawSetShadow(InvEditar[7], 0);
	TextDrawBackgroundColor(InvEditar[7], 255);
	TextDrawFont(InvEditar[7], 4);
	TextDrawSetProportional(InvEditar[7], 0);
	TextDrawSetSelectable(InvEditar[7], true);

	InvEditar[8] = TextDrawCreate(403.750000, 372.583343, "LD_CHAT:thumbdn");
	TextDrawTextSize(InvEditar[8], 39.000000, 42.000000);
	TextDrawAlignment(InvEditar[8], 1);
	TextDrawColor(InvEditar[8], -81);
	TextDrawSetShadow(InvEditar[8], 0);
	TextDrawBackgroundColor(InvEditar[8], 255);
	TextDrawFont(InvEditar[8], 4);
	TextDrawSetProportional(InvEditar[8], 0);
	TextDrawSetSelectable(InvEditar[8], true);

    InvEditar[9] = TextDrawCreate(451.024719, 387.783843, "MUDAR");
	TextDrawLetterSize(InvEditar[9], 0.509374, 2.299998);
	TextDrawTextSize(InvEditar[9], 511.600097, 20.000000);
	TextDrawAlignment(InvEditar[9], 1);
	TextDrawColor(InvEditar[9], -1);
	TextDrawUseBox(InvEditar[9], 1);
	TextDrawBoxColor(InvEditar[9], 16777045);
	TextDrawSetShadow(InvEditar[9], 0);
	TextDrawBackgroundColor(InvEditar[9], 255);
	TextDrawFont(InvEditar[9], 1);
	TextDrawSetProportional(InvEditar[9], 1);
	TextDrawSetSelectable(InvEditar[9], true);


    #if defined OnGameModeInt
		return NA_OnGameModeInt();
	#else
		return 0;
	#endif
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    // apertou F ou ENTER  //
	if(newkeys == KEY_SECONDARY_ATTACK)
	{
	    cmd_movercamera(playerid, "");
	}

	#if defined NA_OnPlayerKeyStateChange
		return NA_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 0;
	#endif
}

stock editar_SetPlayerAttachedObject(playerid, index, modelid, bone, Float:fOffsetX=0.0, Float:fOffsetY=0.0, Float:fOffsetZ=0.0, Float:fRotX=0.0, Float:fRotY=0.0, Float:fRotZ=0.0, Float:fScaleX=0.0, Float:fScaleY=0.0, Float:fScaleZ=0.0, materialcolor1=0, materialcolor2=0)
{
	if(index > -1 && index < 10)
	{
	    Editado[playerid][index][Edit_X] = fOffsetX;
	    Editado[playerid][index][Edit_Y] = fOffsetY;
	    Editado[playerid][index][Edit_Z] = fOffsetZ;
	    Editado[playerid][index][Edit_RX] = fRotX;
	    Editado[playerid][index][Edit_RY] = fRotY;
	    Editado[playerid][index][Edit_RZ] = fRotZ;
	    Editado[playerid][index][Edit_TX] = fScaleX;
	    Editado[playerid][index][Edit_TY] = fScaleY;
	    Editado[playerid][index][Edit_TZ] = fScaleZ;
	    Editado[playerid][index][Edit_Index] = index;
	    Editado[playerid][index][Edit_Bone] = bone;
	    Editado[playerid][index][Edit_Modelo] = modelid;
	}
    SetPlayerAttachedObject(playerid, index, modelid, bone, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ, materialcolor1, materialcolor2);
	return 1;
}


//OnPlayerConnect(playerid)
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect NA_OnPlayerConnect

#if defined NA_OnPlayerConnect
	forward NA_OnPlayerConnect(playerid);
#endif




//OnPlayerDisconnect(playerid, reason)
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect NE_OnPlayerDisconnect

#if defined NE_OnPlayerDisconnect
	forward NE_OnPlayerDisconnect(playerid, reason);
#endif



//OnPlayerSpawn(playerid)
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn NA_OnPlayerSpawn

#if defined NA_OnPlayerSpawn
	forward NA_OnPlayerSpawn(playerid);
#endif


//OnPlayerClickTextDraw( playerid, Text:clickedid )
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif

#define OnPlayerClickTextDraw NA_OnPlayerClickTextDraw

#if defined NA_OnPlayerClickTextDraw
	forward NA_OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif



//OnPlayerDeath(playerid, killerid, reason)
#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif

#define OnPlayerDeath NA_OnPlayerDeath

#if defined NA_OnPlayerDeath
	forward NA_OnPlayerDeath(playerid, killerid, reason);
#endif



//OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif

#define OnPlayerKeyStateChange NA_OnPlayerKeyStateChange

#if defined NA_OnPlayerKeyStateChange
	forward NA_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif




#if defined _ALS_SetPlayerAttachedObject
  #undef SetPlayerAttachedObject
#else
	#define _ALS_SetPlayerAttachedObject
#endif

#define SetPlayerAttachedObject editar_SetPlayerAttachedObject







