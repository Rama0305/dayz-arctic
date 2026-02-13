enum cadss
{
 	cadastro_Existe,
 	cadastro_VPN,
	cadastro_Nick[MAX_PLAYER_NAME]
};


// nado flutuante //
enum dans
{
	df_Existe,
	DynamicText3D:df_3D
};

enum minaa
{
	mina_Existe,
	mina_Base,
	mina_Obj,
	DynamicText3D:mina_3D,
	mina_Dono[40],
	Float:mina_X,
	Float:mina_Y,
	Float:mina_Z
};



enum atendi
{
	at_Existe,
	at_Prioridade,
	at_Player[MAX_PLAYER_NAME],
	at_Admin[MAX_PLAYER_NAME],
	at_Iniciado,
	at_Atendido,
	at_Finalizado
};



// sistema de rank PVP //
enum ranks
{
	rank_Nome[40],
	rank_Modelo,
	rank_Cor
};



// teleportes //
enum teles
{
	tele_Nome[100],
	Float:tele_X,
	Float:tele_Y,
	Float:tele_Z,
	tele_Interior,
	tele_Mundo
};



// baus de Itens //
enum bauss
{
	bau_Existe,
	bau_Base,
	bau_Obj,
	DynamicText3D:bau_3D,
	bau_Madeira,
	bau_Metal,
	bau_Pedra,
	bau_Polvora,
	bau_Sucata,
	Float:bau_X,
	Float:bau_Y,
	Float:bau_Z,
	Float:bau_RX,
	Float:bau_RY,
	Float:bau_RZ
};

//  explosivo c-4 //
enum explo
{
	explosivo_Mundo,
	explosivo_ID_Objeto,
	explosivo_Tipo_Objeto,
	explosivo_Interior,
	explosivo_Existe,
	explosivo_Dono[MAX_PLAYER_NAME],
	Float:explosivo_X,
	Float:explosivo_Y,
	Float:explosivo_Z,
	explosivo_Obj,
	DynamicText3D:explosivo_3D
};



// itens //
enum info_itens
{
	item_Recicladora,
    Float:item_DropDZ,
	Float:item_DropX,
	Float:item_DropY,
    Float:item_PreX,
	Float:item_PreY,
	Float:item_PreZ,
	Float:item_PreV,
	item_Cor,
	item_Cor2,
	item_ID,
	item_Modelo,
	item_Tipo,
	item_Nome[60],
	item_Combinavel,
	item_Info[200]
};

// tutorial //
enum tuto
{
	tuto_Interior,
	tuto_Mundo,
	Float:tuto_X1,
	Float:tuto_Y1,
	Float:tuto_Z1,
	Float:tuto_X2,
	Float:tuto_Y2,
	Float:tuto_Z2,
	Float:tuto_X3,
	Float:tuto_Y3,
	Float:tuto_Z3,
	tuto_Tempo,
	tuto_Clima,
	tuto_Titulo[40],
	tuto_Texto[600]
};





// armas nas costas //
enum armsco
{
	ac_ID,
	ac_Modelo,
	ac_Slot,
	ac_Local,
	Float:ac_X,
	Float:ac_Y,
	Float:ac_Z,
	Float:ac_RX,
	Float:ac_RY,
	Float:ac_RZ,
	Float:ac_TX,
	Float:ac_TY,
	Float:ac_TZ
};



enum clas
{
	classe_Cor,
	classe_Nome[50],
	classe_SkinH,
	classe_SkinM,
	classe_Nivel,
	classe_Info[120],
	classe_Habilidade1[120],
	classe_Habilidade2[120],
	classe_Habilidade3[120],
	classe_Habilidade4[120],
	classe_Habilidade5[120]
};



// classes bases //
enum classbas
{
	classe_Cor,
	classe_Nome[50],
	classe_Level
};




// jbls //
enum jbls
{
	jbl_Existe,
	jbl_Dono[MAX_PLAYER_NAME],
	Float:jbl_X,
	Float:jbl_Y,
	Float:jbl_Z,
	jbl_Interior,
	jbl_Mundo,
	jbl_Link[250],
	jbl_Distancia
};




//  AIR DROP //
enum drops
{
	drop_Existe,
	drop_Obj,
	drop_Obj2,
	drop_Obj3,
	drop_Timer,
	drop_Contar,
	drop_Gz,
	DynamicText3D:drop_3D
};


enum rad
{
    SV_GSTREAM:r_Canal,
    r_Nome[80],
    Float:r_X,
    Float:r_Y,
    Float:r_Z,
    Float:r_R
};




enum
{
    MENU_LOJA_CASH,
    MENU_LISTA_ITENS,
    MENU_LISTA_OBJETOS_BASE,
    MENU_LISTA_CRAFT,
    MENU_CADASTROS
};




enum menuu
{
	menu_ID,
	menu_Nome[200],
	menu_Info[200],
	menu_Unidades,
	menu_Tipo,
	menu_Modelo,
	menu_Valor
};



enum invaa
{
	inv_ID,
	inv_Unidades,
	inv_Tipo,
	inv_Visto
};



//  mesas de Craft  //
enum mesa
{
    me_Obj,
	DynamicText3D:me_3D,
	me_Existe,
	me_Base,
	Float:me_X,
	Float:me_Y,
	Float:me_Z,
	Float:me_RX,
	Float:me_RY,
	Float:me_RZ
};


// opcoes de craft da mesa //
enum objse1
{
	craft_Sucata,
	craft_Madeiras,
	craft_Metais,
	craft_Pedras,
	craft_Polvoras,
	craft_ID

};



// recicladoras //
enum recicles_p
{
	re_Base,
	re_Reciclando,
	re_Sucata,
	re_Tempo,
	re_ID[SLOTS_RECICLADORA],
	re_Unidades[SLOTS_RECICLADORA],
	re_Tipo[SLOTS_RECICLADORA],
	re_Timer
};
enum recicles
{
	re_Existe,
	re_Base,
	re_Obj,
	DynamicText3D:re_3D,
	Float:re_X,
	Float:re_Y,
	Float:re_Z,
	Float:re_RX,
	Float:re_RY,
	Float:re_RZ
};




// Loot de Itens //
enum loooot
{
	loot_Existe,
	loot_Classe,
	Float:loot_X,
	Float:loot_Y,
	Float:loot_Z,
	Float:loot_RX,
	Float:loot_RY,
	Float:loot_RZ,
	loot_Obj,
	loot_Colisao,
	loot_Mapa,
	DynamicText3D:loot_3D
};




// veiculos quebrados //
enum fva
{
	fv_Existe,
	fv_Veiculo,
	fv_ModeloCarro,
	Float:fv_X,
	Float:fv_Y,
	Float:fv_Z,
	Float:fv_A,
	fv_Pneus2,
	fv_Pneus,
	fv_Motor,
	fv_Bateria,
	fv_Metais_Precisa,
	fv_Metais,
	fv_Sucata_Precisa,
	fv_Sucata,
	fv_Polvora_Precisa,
	fv_Polvora
};




// sistema de tunning //
enum ofcs
{
	o_Existe,
	DynamicText3D:o_3D2,
	o_Pickup2,
	o_Mapa2,
	DynamicText3D:o_3D,
	o_Pickup,
	o_Mapa,
	Float:o_X,
	Float:o_Y,
	Float:o_Z,
	o_Obj[36],
	o_Colisao[36]
};



enum pos_ofc
{
	ofc_ID,
	Float:ofc_X,
	Float:ofc_Y,
	Float:ofc_Z,
	Float:ofc_RX,
	Float:ofc_RY,
	Float:ofc_RZ
};





enum tung
{
	t_Nome[40],
	t_Modelo,
	t_Madeiras,
	t_Metais,
	t_Pedras,
	t_Polvoras
};



// baru sampe sini lanjut besok
// comandos //
enum cmdsadm
{
	cmd_Comando[40],
	cmd_Level
};




enum cmdspla
{
	c_Comando[50],
	c_Info[100]
};




// mercado negro //
enum mn
{
	mn_EntrarPickup,
	mn_SairPickup,
	mn_Mapa,
	DynamicText3D:mn_Entrar3D,
	DynamicText3D:mn_Sair3D,
	mn_Existe,
	Float:mn_EntrarX,
	Float:mn_EntrarY,
	Float:mn_EntrarZ,
	Float:mn_SairX,
	Float:mn_SairY,
	Float:mn_SairZ,
	mn_Interior

};


// npcs de locais //
enum actors
{
    DynamicText3D:a_3D,
	a_Actor,
	a_Existe,
	a_Nome[MAX_PLAYER_NAME],
	a_Skin,
	a_Animacao,
	a_Anim1[40],
	a_Anim2[40],
	Float:a_X,
	Float:a_Y,
	Float:a_Z,
	Float:a_A,
	a_Mundo,
	a_Interior
};



enum tan
{
	tanModelo,
	Float:tanX,
	Float:tanY,
	Float:tanZ
};



enum foguei
{
	f_Obj,
	DynamicText3D:f_3D,
	Float:f_X,
	Float:f_Y,
	Float:f_Z,
	Float:f_A,
	f_Existe,
	f_Dono[MAX_PLAYER_NAME],
	f_Vida,
	f_Slot[5],
	f_Pronto[5]
};




enum fog
{
	tf_Nome[50],
	tf_ID,
	tf_Unidades,
	tf_Ferramenta1,
	tf_Ferramenta2,
	tf_Ferramenta3,
	tf_Ingrediente1,
	tf_Ingrediente2,
	tf_Ingrediente3
};





// AREAS DE GAS //
enum area
{
	area_Tipo,
	area_GZ,
	area_Altura,
	area_Largura,
	Float:area_X,
	Float:area_Y,
	area_Nome[40]
};



// objetos //
enum objse
{
	Float:obj_XD,
	Float:obj_YD,
	Float:obj_ZD,
	Float:obj_RD,
	obj_Madeiras,
	obj_Metais,
	obj_Pedras,
	obj_Polvoras,
	obj_Tipo,
	obj_Modelo,
	obj_Nome[40]
};


enum objs
{
    DynamicText3D:obj_3D,
    obj_Tipo,
    obj_Dinamite,
	obj_Colisao,
	obj_Existe,
	Float:obj_X,
	Float:obj_Y,
	Float:obj_Z,
	Float:obj_RX,
	Float:obj_RY,
	Float:obj_RZ,
	obj_ID,
	obj_Base,
	obj_Obj,
	obj_Obj2,
	obj_Status,
	obj_Vida
};



// portoes eletricos //
enum port
{
	portao_Existe,
	portao_Dinamite,
	portao_Vida,
	portao_Modelo,
	portao_Aberto,
	portao_Senha[8],
	portao_Colisao,
	portao_Obj,
	DynamicText3D:portao_3D,
	Float:portao_X1,
	Float:portao_Y1,
	Float:portao_Z1,
	Float:portao_RX1,
	Float:portao_RY1,
	Float:portao_RZ1,
	Float:portao_X2,
	Float:portao_Y2,
	Float:portao_Z2,
	Float:portao_RX2,
	Float:portao_RY2,
	Float:portao_RZ2,
	portao_Mundo,
	portao_Interior,
	portao_Timer,
	portao_Base
};



// caixas de itens //
enum cai
{
    caixa_Existe,
    caixa_Dinamite,
    caixa_Base,
	Float:caixa_X,
	Float:caixa_Y,
	Float:caixa_Z,
	Float:caixa_RX,
	Float:caixa_RY,
	Float:caixa_RZ,
	caixa_ID[MAX_SLOTS],
	caixa_Unidades[MAX_SLOTS],
	caixa_Tipo[MAX_SLOTS],
	DynamicText3D:caixa_3D,
	caixa_Obj,
	caixa_Trancada
};






// sistema de bases //
enum bas
{
	base_Existe,
	base_Level,
	base_Classe,
	base_XP,
	Float:base_X,
	Float:base_Y,
	Float:base_Z,
	base_Pickup,
	base_Nome[40],
	DynamicText3D:base_3D
};



// sistema de admins //
enum adms
{
	adm_Existe,
	adm_Nome[MAX_PLAYER_NAME],
	adm_Level,
	adm_Funcao[40],
	adm_Responssavel[MAX_PLAYER_NAME],
	adm_Dia,
	adm_Mes,
	adm_Ano,
	adm_Hora,
	adm_Minuto,
	adm_Segundo,
	adm_Nota,
	adm_Atendimentos
};

// enum adms
// {
//     adm_Existe,             // adm_Existe
//     adm_Name[MAX_PLAYER_NAME],  // adm_Nome
//     adm_Level,              // adm_Level
//     adm_Role[40],           // adm_Funcao (funguasi / jabatan)
//     adm_Responsible[MAX_PLAYER_NAME], // adm_Responssavel (penanggung jawab)
// 	adm_Serial[101],        // admin player serial (unique identifier)
//     adm_Day,                // adm_Dia
//     adm_Month,              // adm_Mes
//     adm_Year,               // adm_Ano
//     adm_Hour,               // adm_Hora
//     adm_Minute,             // adm_Minuto
//     adm_Second,             // adm_Segundo
//     adm_Notes,              // adm_Nota
//     adm_Supports            // adm_Atendimentos (jumlah tiket/bantuan ditangani)
// };





//sistema de salas //
enum maps
{
	mapa_Nome[100],
	mapa_Interior,
	mapa_Mundo,
	Float:mapa_X,
	Float:mapa_Y,
	mapa_L,
	mapa_A
};



enum sals
{
	sala_Existe,
	sala_Nome[60],
	sala_Senha,
	sala_Tempo,
	sala_Mapa,
	sala_Rounds,
	sala_Round,
	sala_Jogando,
	sala_Preparando,
	sala_Timer,
	sala_Gz,
	sala_Tempo1,
	sala_PlacarB,
	sala_PlacarR
};



// postos de gasolina //
enum post
{
	posto_Existe,
	posto_Litros,
	DynamicText3D:posto_3D,
	posto_Pickup,
	posto_Mapa,
	posto_ID,
	posto_Nome[40],
	Float:posto_X,
	Float:posto_Y,
	Float:posto_Z
};



//   acoes dos players //
enum carg
{
	b_Acao,
	b_Anim,
	b_Anim1[40],
	b_Anim2[40],
	b_Lop,
	b_Barra,
	b_Adicionar,
	b_Timer,
	b_Nome[100]

};



enum cam
{
	ca_Existe,
	Float:ca_X,
	Float:ca_Y,
	Float:ca_Z,
	Float:ca_A,
	Float:ca_XX,
	Float:ca_YY,
	Float:ca_ZZ,
	ca_Dono[MAX_PLAYER_NAME],
	ca_Nome[100],
	ca_Obj,
	ca_Mundo,
	ca_Base,
	ca_Interior
};


// arvores e pedras //
enum arv
{
	ar_Existe,
	DynamicText3D:ar_3D,
	ar_Obj,
	Float:ar_X,
	Float:ar_Y,
	Float:ar_Z,
	Float:ar_A,
	ar_Vida,
	ar_Interior,
	ar_Mundo,
	ar_Player

};



enum arm
{
	a_Item,
	a_ID,
	a_Modelo,
	Float:a_Dano,
	a_Slot,
	a_Nome[40]
};



// Zombies //
enum zom
{
    z_Spawn,
    z_Existe,
	z_Zombie,
	z_Tipo,
	z_Actor,
	z_Capacete,
	z_Colete,
	z_Mascara,
	z_Skin,
	z_Timer,
	z_Vida,
	z_Alvo,
	Float:z_X,
	Float:z_Y,
	Float:z_Z,
	Float:z_A,
	z_Arma,
	z_Municao
};


// equipamentos das Skins //
enum equip
{
	Float:xx,
	Float:yy,
	Float:zz,
	Float:rxx,
	Float:ryy,
	Float:rzz,
	Float:tx,
	Float:ty,
	Float:tz
};



enum playerinfo
{
	pMissaoDia,
	pMissaoColetado,
	pMissao[100],
	pDia,
	pMes,
	pAno,
	pHora,
	pMinuto,
	pSegundo,
	pGrana2,
	pGrana,
	pCash,
	pSkin,
	pLevel,
	pXP,
	pRank,
	pXPH,
	pInterior,
	pMundo,
	Float:pX,
	Float:pY,
	Float:pZ,
	Float:pA,
	pConfig[7],
	pJogado,
	pUpar,
	pClasse,
	pVivo,
	pMorreu,
	pMatou,
	pZombies,
	pSono,
	pFrio,
	pFome,
	pSede,
	pSexo,
	pVip,
	pLobby,
	pTutorial,
	pArmaMorreu,
	pIP[100],
	pCadeia,
	pCadeiaMotivo[150],
	pCadeiaAdmin[MAX_PLAYER_NAME],
	pKiller[MAX_PLAYER_NAME]
};



// PLAYER //
enum inv
{
	inv_ID,
	inv_Unidades,
	inv_Tipo
};



// veiculos //
enum vei
{
    Float:v_Vida,
    v_Cadeado,
    v_Existe,
	v_ID,
	v_Dono[MAX_PLAYER_NAME],
	v_Modelo,
	v_Gasolina,
	v_Bateria,
	v_Lataria,
	v_Trancado,
	v_Cor1,
	v_Cor2,
	v_Base,
	Float:v_X,
	Float:v_Y,
	Float:v_Z,
	Float:v_A,
	v_Pneu[4],
	v_Obj[MAX_TUNINGS],
	v_Obj_Existe[MAX_TUNINGS],
	v_Obj_ID[MAX_TUNINGS],
	Float:v_Obj_X[MAX_TUNINGS],
	Float:v_Obj_Y[MAX_TUNINGS],
	Float:v_Obj_Z[MAX_TUNINGS],
	Float:v_Obj_RX[MAX_TUNINGS],
	Float:v_Obj_RY[MAX_TUNINGS],
	Float:v_Obj_RZ[MAX_TUNINGS],
	v_Timer

};




// DIALOGGS DO SERVIDOR //
enum
{
    DIALOG_VAZIO,
    DIALOG_CONTA,
    DIALOG_CONTA2,
    DIALOG_MEMBROS,
    DIALOG_MEMBROS2,
    DIALOG_CONFIGURACOES,
    DIALOG_COLOCAR_EXPLOSIVO,
    DIALOG_MUNICOES,
    DIALOG_NOVIDADES,
    DIALOG_TROCAR_NICK,
    DIALOG_NOVO_NICK,
    DIALOG_ATENDIMENTOS,
    DIALOG_ATENDIMENTO,
    DIALOG_CARROS,
    DIALOG_BASES,
    DIALOG_ZOMBIE,
    DIALOG_ADMINS,
    DIALOG_ADMINS2,
    DIALOG_PORTA_MALAS,
    DIALOG_OPCAO_PORTA_MALAS,
    DIALOG_MONTAR_CARRO,
    DIALOG_MONTAR_CARRO2,
    DIALOG_TUTO,
    DIALOG_PLATAFORMA,
    DIALOG_TELEPORTES,
    DIALOG_LISTA_ADMIN,
    DIALOG_LISTA_ADMIN2,
    DIALOG_LISTA_ADMIN3,
    DIALOG_LISTA_ADMIN4,
    DIALOG_LISTA_ADMIN5,
    DIALOG_LOGS,
    DIALOG_LOGS2,
    DIALOG_BAU,
    DIALOG_BAU2,
    DIALOG_BAU3,
    DIALOG_CLIMA,
    DIALOG_EXPLOSIVOS,
    DIALOG_HACK_PORTAO,
    DIALOG_HACK_VEICULO,
    DIALOG_HACK_PLAYER,
    DIALOG_CONFIRMAR,
    DIALOG_SEXO,
    DIALOG_SKIN_CLASSE,
    DIALOG_RADIO,
    DIALOG_RADIO2,
    DIALOG_RADIO3,
    DIALOG_EXCLUIR_Lobby,
    DIALOG_MESA,
    DIALOG_MESA2,
    DIALOG_DROPAR,
    DIALOG_DROPAR2,
    DIALOG_RECICLADORA,
    DIALOG_RECICLADORA2,
    DIALOG_RECICLADORA3,
    DIALOG_RECICLADORA4,
    DIALOG_EXCLUIR_VEICULO,
    DIALOG_EDITAR_VEICULO,
    DIALOG_EDITAR_VEICULO2,
    DIALOG_EDITAR_VEICULO3,
    DIALOG_TUNINGS,
    DIALOG_TUNINGS2,
    DIALOG_TUNINGS3,
    DIALOG_AJUDA,
    DIALOG_AJUDA2,
    DIALOG_ITENS,
    DIALOG_ITENS2,
    DIALOG_PNEUS,
    DIALOG_MONTAR_ARMA,
    DIALOG_MONTAR_ARMA2,
    DIALOG_MERCADO_NEGRO,
	DIALOG_BASE13,
	DIALOG_BASE16,
	DIALOG_PORTAO5,
	DIALOG_PORTAO4,
	DIALOG_PORTAO2,
	DIALOG_PORTAO,
	DIALOG_CAIXA3,
	DIALOG_CAIXA2,
	DIALOG_CAIXA,
	DIALOG_BASE,
	DIALOG_BASE2,
	DIALOG_BASE3,
	DIALOG_BASE4,
	DIALOG_BASE5,
	DIALOG_BASE6,
	DIALOG_BASE7,
	DIALOG_BASE8,
	DIALOG_BASE9,
	DIALOG_BASE10,
	DIALOG_BASE11,
	DIALOG_BASE12,
	DIALOG_BASE14,
	DIALOG_BASE15,
	DIALOG_ERRO,
	DIALOG_SEPARAR,
	DIALOG_DESTRUIR_ARVORE,
	DIALOG_DESTRUIR_PEDRA,
	DIALOG_CAMERAS,
	DIALOG_CAMERAS2,
	DIALOG_CAMERAS3,
	DIALOG_KIKAR_SALA,
	DIALOG_CONVIDAR_SALA,
	DIALOG_CONVIDAR_SALA2,
	DIALOG_PVP,
	DIALOG_CRIAR_CONTA,
	DIALOG_LOGAR,
	DIALOG_FOGUEIRA,
	DIALOG_FOGUEIRA1,
	DIALOG_FOGUEIRA2,
	DIALOG_FOGUEIRA3,
	DIALOG_FOGUEIRA4,
	DIALOG_VEICULOS,
	DIALOG_VEICULOS2,
	DIALOG_ANIMS_INCLUDE,
	DIALOG_ANIMS_INCLUDE2
};




// recolher itens //
enum itens_recolher
{
	item_Obj,
	item_Existe,
	item_Deletar,
	item_ID,
	item_Unidades,
	item_Tipo,
	Float:item_X,
	Float:item_Y,
	Float:item_Z,
	item_Mundo,
	item_Interior

};



enum infos_z
{
	zi_Skin,
	zi_Vida,
	zi_Arma,
	zi_Municao,
	zi_Capacete,
	zi_Colete,
	zi_Mascara
};


enum apags
{
	apags_Existe,
	DynamicText3D:apags_3D
};