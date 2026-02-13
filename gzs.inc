#define MAX_GZS 200

enum gzz
{
	gzExiste,
	gzGZ_Existe[4],
	gzGZ[4],
	Float:gzX,
	Float:gzY,
	Float:gzA,
	Float:gzL,
	gzTipo,
	gzCor
};
new gz[MAX_GZS][gzz];


/*

native GZ_PlayerInGz(playerid, i);
native GZ_CorGz(i, 0xFFFFFFFF);
native GZ_TipoGz(i, 0 1 ou 2 );
native GZ_DestruirGz(i);
native GZ_CriarGz(Float:xxx, Float:yyy, Float:aaa, Float:lll, 0 1 ou 2, 0xffffffff);
native GZ_MostrarGzPlayer(playerid, i);
native GZ_MostrarGzTodos(i);
native GZ_EsconderGzPlayer(playerid, i);
native GZ_EsconderGzTodos(i);
native GZ_PiscarGzPlayer(playerid, i);
native GZ_PiscarGzTodos(i);
native GZ_PararDePiscarGzPlayer(playerid, i);
native GZ_PararDePiscarGzTodos(i);
native GZ_PegarGzPlayer(playerid);


*/


stock GZ_PegarGzPlayer(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    new Float:pli[3];
	    GetPlayerPos(playerid, pli[0],pli[1],pli[2]);
	    for(new i=1; i<MAX_GZS; i++)
	    {
	        if(gz[i][gzExiste] == 0) continue;
    		if(pli[0] >= gz[i][gzX]-gz[i][gzL]/2 && pli[0] <= gz[i][gzX]+gz[i][gzL]/2 &&
			pli[1] >= gz[i][gzY]-gz[i][gzA]/2 && pli[1] <= gz[i][gzY]+gz[i][gzA]/2 )return i;
		}
	}
	return 0;
}


stock GZ_PararDePiscarGzTodos(i, corr)
{
    if(i < 1 || i >= MAX_GZS) return 1;
    if(gz[i][gzExiste] == 1)
	{
    	for(new a; a<MAX_PLAYERS; a++)
		{
		    if(!IsPlayerConnected(a)) continue;
	        if(gz[i][gzGZ_Existe][0] != 0) GangZoneStopFlashForPlayer(a, gz[i][gzGZ][0]);
	        if(gz[i][gzGZ_Existe][1] != 0) GangZoneStopFlashForPlayer(a, gz[i][gzGZ][1]);
	        if(gz[i][gzGZ_Existe][2] != 0) GangZoneStopFlashForPlayer(a, gz[i][gzGZ][2]);
	        if(gz[i][gzGZ_Existe][3] != 0) GangZoneStopFlashForPlayer(a, gz[i][gzGZ][3]);
	    }
	}
	return 1;
}

stock GZ_PararDePiscarGzPlayer(playerid, i, corr)
{
    if(i < 1 || i >= MAX_GZS) return 1;
    if(IsPlayerConnected(playerid))
	{
	    if(gz[i][gzExiste] == 1)
	    {
	        if(gz[i][gzGZ_Existe][0] != 0) GangZoneStopFlashForPlayer(playerid, gz[i][gzGZ][0]);
	        if(gz[i][gzGZ_Existe][1] != 0) GangZoneStopFlashForPlayer(playerid, gz[i][gzGZ][1]);
	        if(gz[i][gzGZ_Existe][2] != 0) GangZoneStopFlashForPlayer(playerid, gz[i][gzGZ][2]);
	        if(gz[i][gzGZ_Existe][3] != 0) GangZoneStopFlashForPlayer(playerid, gz[i][gzGZ][3]);
	    }
	}
	return 1;
}

stock GZ_PiscarGzPlayer(playerid, i, corr)
{
    if(i < 1 || i >= MAX_GZS) return 1;
    if(IsPlayerConnected(playerid))
	{
	    if(gz[i][gzExiste] == 1)
	    {
	        if(gz[i][gzGZ_Existe][0] != 0) GangZoneFlashForPlayer(playerid, gz[i][gzGZ][0], corr);
	        if(gz[i][gzGZ_Existe][1] != 0) GangZoneFlashForPlayer(playerid, gz[i][gzGZ][1], corr);
	        if(gz[i][gzGZ_Existe][2] != 0) GangZoneFlashForPlayer(playerid, gz[i][gzGZ][2], corr);
	        if(gz[i][gzGZ_Existe][3] != 0) GangZoneFlashForPlayer(playerid, gz[i][gzGZ][3], corr);
	    }
	}
	return 1;
}

stock GZ_PiscarGzTodos(i, corr)
{
    if(i < 1 || i >= MAX_GZS) return 1;
    for(new a; a<MAX_PLAYERS; a++)
	{
	    if(!IsPlayerConnected(a)) continue;
	    if(gz[i][gzExiste] == 1)
	    {
	        if(gz[i][gzGZ_Existe][0] != 0) GangZoneFlashForPlayer(a, gz[i][gzGZ][0], corr);
	        if(gz[i][gzGZ_Existe][1] != 0) GangZoneFlashForPlayer(a, gz[i][gzGZ][1], corr);
	        if(gz[i][gzGZ_Existe][2] != 0) GangZoneFlashForPlayer(a, gz[i][gzGZ][2], corr);
	        if(gz[i][gzGZ_Existe][3] != 0) GangZoneFlashForPlayer(a, gz[i][gzGZ][3], corr);
	    }
	}
	return 1;
}

stock GZ_EsconderGzPlayer(playerid, i)
{
    if(i < 1 || i >= MAX_GZS) return 1;
    if(IsPlayerConnected(playerid))
	{
	    if(gz[i][gzExiste] == 1)
	    {
	        if(gz[i][gzGZ_Existe][0] != 0) GangZoneHideForPlayer(playerid, gz[i][gzGZ][0]);
	        if(gz[i][gzGZ_Existe][1] != 0) GangZoneHideForPlayer(playerid, gz[i][gzGZ][1]);
	        if(gz[i][gzGZ_Existe][2] != 0) GangZoneHideForPlayer(playerid, gz[i][gzGZ][2]);
	        if(gz[i][gzGZ_Existe][3] != 0) GangZoneHideForPlayer(playerid, gz[i][gzGZ][3]);
	    }
	}
	return 1;
}

stock GZ_EsconderGzTodos(i)
{
    if(i < 1 || i > MAX_GZS-1) return 1;
	for(new a; a<MAX_PLAYERS; a++)
	{
	    if(!IsPlayerConnected(a)) continue;
	    if(gz[i][gzExiste] == 1)
	    {
	        if(gz[i][gzGZ_Existe][0] != 0) GangZoneHideForPlayer(a, gz[i][gzGZ][0]);
	        if(gz[i][gzGZ_Existe][1] != 0) GangZoneHideForPlayer(a, gz[i][gzGZ][1]);
	        if(gz[i][gzGZ_Existe][2] != 0) GangZoneHideForPlayer(a, gz[i][gzGZ][2]);
	        if(gz[i][gzGZ_Existe][3] != 0) GangZoneHideForPlayer(a, gz[i][gzGZ][3]);
	    }
	}

	return 1;
}

stock GZ_PlayerInGz(playerid, i)
{
    if(i < 1 || i > MAX_GZS-1) return 0;
	if(IsPlayerConnected(playerid))
	{
	    if(gz[i][gzExiste] == 1)
		{
		    new Float:pli[3];
		    GetPlayerPos(playerid, pli[0],pli[1],pli[2]);
		    if(pli[0] >= gz[i][gzX]-gz[i][gzL]/2 && pli[0] <= gz[i][gzX]+gz[i][gzL]/2 &&
			pli[1] >= gz[i][gzY]-gz[i][gzA]/2 && pli[1] <= gz[i][gzY]+gz[i][gzA]/2 )return 1;
	    }
	}
	return 0;
}


stock GZ_CorGz(i, corr)
{
    if(i < 1 || i > MAX_GZS-1) return 1;
    if(gz[i][gzExiste] == 1)
	{
	    gz[i][gzCor] = corr;
	}
	return 1;
}

stock GZ_TipoGz(i, tips)
{
    if(i < 1 || i > MAX_GZS-1) return 1;
	if(gz[i][gzExiste] == 1)
	{
        gz[i][gzTipo] = tips;
        if(gz[i][gzGZ_Existe][0] != 0 ) GangZoneDestroy(gz[i][gzGZ][0]);
        if(gz[i][gzGZ_Existe][1] != 0 ) GangZoneDestroy(gz[i][gzGZ][1]);
        if(gz[i][gzGZ_Existe][2] != 0 ) GangZoneDestroy(gz[i][gzGZ][2]);
        if(gz[i][gzGZ_Existe][3] != 0 ) GangZoneDestroy(gz[i][gzGZ][3]);
        gz[i][gzGZ_Existe][0] = 0;
	    gz[i][gzGZ_Existe][1] = 0;
	    gz[i][gzGZ_Existe][2] = 0;
	    gz[i][gzGZ_Existe][3] = 0;

		if(tips == 0)
		{
		    gz[i][gzGZ][0] = GangZoneCreate( gz[i][gzX]-(gz[i][gzL]/2), gz[i][gzY]-(gz[i][gzA]/2), gz[i][gzX]+(gz[i][gzL]/2), gz[i][gzY]+(gz[i][gzA]/2) );
		    gz[i][gzGZ][1] = -1;
		    gz[i][gzGZ][2] = -1;
		    gz[i][gzGZ][3] = -1;
		    gz[i][gzGZ_Existe][0] = 1;
		    gz[i][gzGZ_Existe][1] = 0;
		    gz[i][gzGZ_Existe][2] = 0;
		    gz[i][gzGZ_Existe][3] = 0;
		}

		if(tips == 1)
		{
		    gz[i][gzGZ][0] = GangZoneCreate( -3000, -3000, gz[i][gzX]-(gz[i][gzL]/2), 3000 );
		    gz[i][gzGZ][1] = GangZoneCreate( gz[i][gzX]+(gz[i][gzL]/2), -3000, 3000, 3000 );
		    gz[i][gzGZ][2] = GangZoneCreate( gz[i][gzX]-(gz[i][gzL]/2), -3000, gz[i][gzX]+(gz[i][gzL]/2), gz[i][gzY]-(gz[i][gzA]/2));
		    gz[i][gzGZ][3] = GangZoneCreate( gz[i][gzX]-(gz[i][gzL]/2), gz[i][gzY]+(gz[i][gzA]/2), gz[i][gzX]+(gz[i][gzL]/2), 3000);
            gz[i][gzGZ_Existe][0] = 1;
		    gz[i][gzGZ_Existe][1] = 1;
		    gz[i][gzGZ_Existe][2] = 1;
		    gz[i][gzGZ_Existe][3] = 1;
		}

		if(tips == 2)
		{
		    gz[i][gzGZ][0] = GangZoneCreate( gz[i][gzX]-(gz[i][gzL]/2), gz[i][gzY]-(gz[i][gzA]/2), (gz[i][gzX]-(gz[i][gzL]/2))+6, gz[i][gzY]+(gz[i][gzA]/2) );
		    gz[i][gzGZ][1] = GangZoneCreate( (gz[i][gzX]+(gz[i][gzL]/2)-6), gz[i][gzY]-(gz[i][gzA]/2), gz[i][gzX]+(gz[i][gzL]/2), gz[i][gzY]+(gz[i][gzA]/2) );
		    gz[i][gzGZ][2] = GangZoneCreate( (gz[i][gzX]-(gz[i][gzL]/2)+6), gz[i][gzY]-(gz[i][gzA]/2), (gz[i][gzX]+(gz[i][gzL]/2)-6), (gz[i][gzY]-(gz[i][gzA]/2)+6) );
			gz[i][gzGZ][3] = GangZoneCreate( (gz[i][gzX]-(gz[i][gzL]/2)+6), (gz[i][gzY]+(gz[i][gzA]/2)-6), (gz[i][gzX]+(gz[i][gzL]/2)-6), gz[i][gzY]+(gz[i][gzA]/2) );
            gz[i][gzGZ_Existe][0] = 1;
		    gz[i][gzGZ_Existe][1] = 1;
		    gz[i][gzGZ_Existe][2] = 1;
		    gz[i][gzGZ_Existe][3] = 1;
		}
		return 1;
	}
	return 1;
}


stock GZ_DestruirGz(&i)
{
	if(i < 1 || i > MAX_GZS-1) return 1;
	if(gz[i][gzExiste] == 1)
	{
        if(gz[i][gzGZ_Existe][0] != 0 ) GangZoneDestroy(gz[i][gzGZ][0]);
        if(gz[i][gzGZ_Existe][1] != 0 ) GangZoneDestroy(gz[i][gzGZ][1]);
        if(gz[i][gzGZ_Existe][2] != 0 ) GangZoneDestroy(gz[i][gzGZ][2]);
        if(gz[i][gzGZ_Existe][3] != 0 ) GangZoneDestroy(gz[i][gzGZ][3]);
        gz[i][gzGZ][0] = -1;
	    gz[i][gzGZ][1] = -1;
	    gz[i][gzGZ][2] = -1;
	    gz[i][gzGZ][3] = -1;

	    gz[i][gzGZ_Existe][0] = 0;
	    gz[i][gzGZ_Existe][1] = 0;
	    gz[i][gzGZ_Existe][2] = 0;
	    gz[i][gzGZ_Existe][3] = 0;
        gz[i][gzExiste] = 0;
	}
	i = 0;
	return 1;
}

stock GZ_CriarGz(Float:xxx, Float:yyy, Float:aaa, Float:lll, tips, cor)
{
	for(new i=1; i<MAX_GZS; i++)
	{
	    if(gz[i][gzExiste] == 0)
	    {
            gz[i][gzExiste] = 1;
            gz[i][gzX] = xxx;
            gz[i][gzY] = yyy;
            gz[i][gzA] = aaa;
            gz[i][gzL] = lll;
            gz[i][gzTipo] = tips;
            gz[i][gzCor] = cor;

            if(gz[i][gzGZ_Existe][0] != 0 ) GangZoneDestroy(gz[i][gzGZ][0]);
            if(gz[i][gzGZ_Existe][1] != 0 ) GangZoneDestroy(gz[i][gzGZ][1]);
            if(gz[i][gzGZ_Existe][2] != 0 ) GangZoneDestroy(gz[i][gzGZ][2]);
            if(gz[i][gzGZ_Existe][3] != 0 ) GangZoneDestroy(gz[i][gzGZ][3]);
            gz[i][gzGZ_Existe][0] = 0;
		    gz[i][gzGZ_Existe][1] = 0;
		    gz[i][gzGZ_Existe][2] = 0;
		    gz[i][gzGZ_Existe][3] = 0;

			if(tips == 0)
			{
			    gz[i][gzGZ][0] = GangZoneCreate( xxx-(lll/2), yyy-(aaa/2), xxx+(lll/2), yyy+(aaa/2) );
			    gz[i][gzGZ][1] = -1;
			    gz[i][gzGZ][2] = -1;
			    gz[i][gzGZ][3] = -1;
			    gz[i][gzGZ_Existe][0] = 1;
			    gz[i][gzGZ_Existe][1] = 0;
			    gz[i][gzGZ_Existe][2] = 0;
			    gz[i][gzGZ_Existe][3] = 0;
			}

			if(tips == 1)
			{
			    gz[i][gzGZ][0] = GangZoneCreate( -3000, -3000, xxx-(lll/2), 3000 );
			    gz[i][gzGZ][1] = GangZoneCreate( xxx+(lll/2), -3000, 3000, 3000 );
			    gz[i][gzGZ][2] = GangZoneCreate( xxx-(lll/2), -3000, xxx+(lll/2), yyy-(aaa/2));
			    gz[i][gzGZ][3] = GangZoneCreate( xxx-(lll/2), yyy+(aaa/2), xxx+(lll/2), 3000);
			    gz[i][gzGZ_Existe][0] = 1;
			    gz[i][gzGZ_Existe][1] = 1;
			    gz[i][gzGZ_Existe][2] = 1;
			    gz[i][gzGZ_Existe][3] = 1;
			}

			if(tips == 2)
			{
			    gz[i][gzGZ][0] = GangZoneCreate( xxx-(lll/2), yyy-(aaa/2), (xxx-(lll/2))+6, yyy+(aaa/2) );
			    gz[i][gzGZ][1] = GangZoneCreate( (xxx+(lll/2)-6), yyy-(aaa/2), xxx+(lll/2), yyy+(aaa/2) );
			    gz[i][gzGZ][2] = GangZoneCreate( (xxx-(lll/2)+6), yyy-(aaa/2), (xxx+(lll/2)-6), (yyy-(aaa/2)+6) );
				gz[i][gzGZ][3] = GangZoneCreate( (xxx-(lll/2)+6), (yyy+(aaa/2)-6), (xxx+(lll/2)-6), yyy+(aaa/2) );
				gz[i][gzGZ_Existe][0] = 1;
			    gz[i][gzGZ_Existe][1] = 1;
			    gz[i][gzGZ_Existe][2] = 1;
			    gz[i][gzGZ_Existe][3] = 1;
			}
            return i;
		}
	}

	return 0;
}

stock GZ_MostrarGzPlayer(playerid, i)
{
    if(i <  1 || i > MAX_GZS-1) return 1;
	if(IsPlayerConnected(playerid))
	{
	    if(gz[i][gzExiste] == 1)
	    {
	        if(gz[i][gzGZ_Existe][0] != 0 ) GangZoneShowForPlayer(playerid, gz[i][gzGZ][0], gz[i][gzCor]);
	        if(gz[i][gzGZ_Existe][1] != 0 ) GangZoneShowForPlayer(playerid, gz[i][gzGZ][1], gz[i][gzCor]);
	        if(gz[i][gzGZ_Existe][2] != 0 ) GangZoneShowForPlayer(playerid, gz[i][gzGZ][2], gz[i][gzCor]);
	        if(gz[i][gzGZ_Existe][3] != 0 ) GangZoneShowForPlayer(playerid, gz[i][gzGZ][3], gz[i][gzCor]);
	    }
	}
	return 1;
}

stock GZ_MostrarGzTodos(i)
{
    if(i < 1 || i > MAX_GZS-1) return 1;
	for(new a; a<MAX_PLAYERS; a++)
	{
	    if(!IsPlayerConnected(a)) continue;
	    if(gz[i][gzExiste] == 1)
	    {
	        if(gz[i][gzGZ_Existe][0] != 0) GangZoneShowForPlayer(a, gz[i][gzGZ][0], gz[i][gzCor]);
	        if(gz[i][gzGZ_Existe][1] != 0) GangZoneShowForPlayer(a, gz[i][gzGZ][1], gz[i][gzCor]);
	        if(gz[i][gzGZ_Existe][2] != 0) GangZoneShowForPlayer(a, gz[i][gzGZ][2], gz[i][gzCor]);
		}
	}
	return 1;
}


