// ant bot
new conectado[MAX_PLAYERS];
new flood_vpn[MAX_PLAYERS];



new Float:fPX, Float:fPY, Float:fPZ, Float:fVX, Float:fVY, Float:fVZ, Float:object_x, Float:object_y;
new Float:fScale = 5.0;



new Cadastros[MAX_CADASTROS][cadss];
new cadastro_player[MAX_PLAYERS];
new cadastrados;



// actors quando morre //
new ActorMorte[MAX_PLAYERS];
new TempoActor[MAX_PLAYERS];


// nado flutuante //
new DanoFlutuante[MAX_DANOS][dans];
new obj_tv_existe[MAX_PLAYERS][50];
new obj_tv[MAX_PLAYERS][50];
new Float:LastHit[MAX_PLAYERS][3];



// textdraw de acao player //
new mostrando_acao[MAX_PLAYERS];



// ligando servidor //
new servidor_ligado;
new etapa;
new timer_ligando;
new etapas[3][300];
new esperando[MAX_PLAYERS];

new tempo_conectar[MAX_PLAYERS];


new Mina[MAX_MINAS][minaa];


// LISTA DE OBJETOS DA DINAMITE //
new ObjetosPerto[MAX_PLAYERS][2][50];


// PASSE DA TEMPORADA //
new TEMPORADA = 1;


// new bool:IsNPCRunning[MAX_PLAYERS];






new TemporadaPlayer[MAX_PLAYERS];
new PlayerPasse[MAX_PLAYERS];
new PasseNivel[MAX_PLAYERS];
new PasseProgresso[MAX_PLAYERS];
new PremioRecolhidoPago[MAX_PLAYERS][MAX_PASSE];
new PremioRecolhidoFree[MAX_PLAYERS][MAX_PASSE];
new PaginaPasseFree[MAX_PLAYERS];
new PaginaPassePago[MAX_PLAYERS];
new ItemPasseFree[MAX_PLAYERS];
new ItemPassePago[MAX_PLAYERS];


// premios do passe de graca //
new PremiosPasseFree[][] =
{
	{2, 10, 0, 1}, // analgesico
	{3, 10, 0, 1}, // reparador
	{5, 5000, 0, 1}, // dinheiro
	{8, 10, 0, 1}, // kit medico
	{15, 1, 100, 1}, // colete 3
	{18, 1, 100, 1}, // capacete 3
	{99, 1, 309, 1}, // skin M
	{80, 10, 0, 1}, // frag sub
	{81, 10, 0, 1}, // frag rifle
	{39, 1, 31, 1}, // M16
	{1, 1, 0, 1} // camera de seguranca
};



// premios do passe pago //
new PremiosPassePago[][] =
{
	{49, 1, 34, 1}, // sniper
	{66, 100, 6, 1}, // municao de sniper
	{5, 20000, 0, 1}, // dinheiro
	{97, 200, 0, 1}, // metais
	{115, 1, TIPO_TINTA, 1}, // tinha verde
	{128, 1, 1, 1}, // cadeado
	{129, 1, 1, 1}, // chave
	{99, 1, 287, 1}, // skin M
	{99, 1, 195, 1}, // skin F
	{125, 1, 470, 1} // PATRIOT
};


// variaveis //
new mostrando_dano_gas[MAX_PLAYERS];
new CARRO_DE_FERRO_VELHO[MAX_VEHICLES];


// verificar rt //
new RT_Player[MAX_PLAYERS];
new RT_Tempo[MAX_PLAYERS];
new RT_Ammo[MAX_PLAYERS];
new RT_Up[MAX_PLAYERS];


// mostrar no mapa //
new Makers[MAX_PLAYERS][MAX_PLAYERS];
new flood_atirou[MAX_PLAYERS];


// lista de caerros //
new pagina_carros[MAX_PLAYERS];
new Lista_Carros[MAX_PLAYERS][MAX_CARROS];


// invineravel ao spawnar //
new invuneravel[MAX_PLAYERS];


new Atendimento[MAX_ATENDIMENTOS][atendi];
new atendimentos_player[MAX_PLAYERS][MAX_ATENDIMENTOS];
new atendimento_admin[MAX_PLAYERS];
new atendimento_player[MAX_PLAYERS];



new novidades[][] =
{
    "{00ff00}17/07/2022 - UPDATE\n",
    "\n",
    "\n",
    "\n",
    "{ffffff}Some {ff0000}BUGS {ffffff}have been fixed, thanks to everyone who reported to the admins.\n",
    "\n",
    //"{ffffff}Now the vehicle can be unlocked directly by pressing the {ffff00}H {ffffff}key if you are the owner.\n",
    //"{ffffff}The C-4 Explosive system has been updated and improved, now only causes damage to players within 5 meters.\n",
    //"{ffffff}Now when you {00ff00}die{ffffff}, you have to wait 5 minutes to enter {ffff00}Story mode {ffffff}again.\n\n",
    //"{ffffff}If you {ff0000}disconnect {ffffff}from the server for any reason while critically injured, items will be dropped.\n\n",
    //"{ffffff}It will not be possible to use the {00ff00}jetpack {ffffff}during Haid hours.\n\n",
    //"{ffffff}You will need the item {00ffff}radio {ffffff}to talk in {00ff00}/g {ffffff}and {00ff00}/par{ffffff}, global chat every 5 minutes.\n\n",
    //"{ffffff}The {00ff00}notebook {ffffff}item has been nerfed, and the satellite now requires map and GPS.\n\n",
    //"{ffffff}Spawn bug in Lobby fixed, the spawn position will now be considered invalid.\n\n",
    //"{ffffff}Waiting time upon {00ffff}death {ffffff}has been fixed.\n",
    //"{ffff00}Haid hours: {ffffff}5 Minutes.\n",
    //"{ffff00}Off hours: {ffffff}1 Minute.\n\n",
    //"{ffffff}Release of the {00ffff}SEASON PASS {a1a1a1}(BETA)\n\n",
    //"{ffffff}The pass can be purchased from the {ffff00}Cash Shop {ffffff}in the Lobby.\n",
    //"{ffffff}The {00ffff}pass level {ffffff}increases with {00ffff}play time {ffffff}in Story mode.\n",
    //"{ffffff}There are 10 {a1a1a1}FREE {ffffff}rewards and 10 {ffff00}PREMIUM{ffffff} rewards, this is a Beta version of the pass.\n",
    //"{ffffff}Soon, players will have some in-game benefits by purchasing the pass.",
    //"\n",
    //"\n",
    //"{ffffff}Change: {00ffff}ITEM BOX\n",
    //"{a1a1a1}Now the Leader or Sub-Leader of the base can lock or unlock the Item Box, if\n",
    //"the Box is locked, it cannot be accessed.\n",
    //"\n",
    //"\n",
    //"{ffffff}Change: {00ffff}MATERIALS CHEST\n",
    //"{a1a1a1}Now the option to take any material from the chest is restricted only to the Leader or\n",
    //"Sub-Leader of the base, storing materials is still possible, contact the Leader or Sub-Leader to take any materials.",
    //"\n",
    //"\n",
    "{ffffff}New Item: {00ffff}LAND MINE\n",
    "{a1a1a1}Can only be used during Haid hours, found in {ffff00}High-Class Chests {a1a1a1}or\n",
    "crafted at {00ff00}Crafting Tables{a1a1a1}, each player can place {00ffff}3{a1a1a1} land mines, the owner or members of the same base\n",
    "do not trigger the land mine; if someone shoots the land mine it will explode as if someone\n",
    "stepped on it.",
    "\n",
    "\n",
    "{ffffff}Change: {00ffff}DEATH SYSTEM\n",
    "{a1a1a1}The Death System (when a player is critically injured) has been modified, check\n",
    "using {ffffff}/help {a1a1a1}>> {ffffff}Death System{a1a1a1} to see the updates and know what to do in this situation.",
    "\n",
    "\n",
    "{ffffff}New: {00ffff}COORDINATE SYSTEM\n",
    "{a1a1a1}Some textdraws have been added below the materials on the right side of your screen in Story mode, this\n",
    "allows more dynamic communication between clans, to share the location of targets more easily and quickly. The camera angle\n",
    "is used, not the character's angle.",
    "\n",
    "\n",
    "{ffffff}New Command: {00ffff}/MEMBERS\n",
    "{a1a1a1}To see the online member list of your base, allowing you to send a\n",
    "private message to the selected member.\n",
    "\n",
    "\n",
    "{ffff00}Scripter",
    "\n"
};



// PUNICAO //





// cameras login //
new camera_player[MAX_PLAYERS];
new idcameraplayer[MAX_PLAYERS];
enum cl
{
	cl_Interior,
	cl_Mundo,
	Float:cl_Pos[12]
};
new camera_login[][cl] =
{
    {0,555, {1095.2092,-2111.5015,65.9396, 1083.4514,-2096.7424,63.3781, 837.5728,-2030.4590,12.8672, 837.5728,-2030.4590,12.8672}},
    {0,555, {1478.7136,-1620.8208,14.0393, 1483.3856,-1622.8085,14.0469, 1483.6602,-1625.6804,13.0469, 1483.6602,-1625.6804,13.0469}},
	{1,555, {2.7543,28.1182,1200.0781, 0.4824,28.7665,1199.5938, 2.5402,29.6497,1199.6012, 2.5402,29.6497,1199.6012}},
	{1,555, {299.3538,-38.9368,1002.5156, 293.9219,-40.9749,1002.5156, 298.2508,-40.9836,1001.5156, 298.2508,-40.9836,1001.5156}},
	{0,555, {1948.9768,-1794.4521,13.5469, 1942.0903,-1783.2537,13.3906, 1939.2593,-1785.9316,13.3906, 1939.2593,-1785.9316,13.3906}},
	{0,555, {-2296.6873,1530.5183,-0.3850, -2305.8689,1538.2908,19.5362,-2305.8689,1538.2908,19.5362, -2305.8689,1538.2908,19.5362}},
	{0,555, {-2225.7344,-1745.3256,481.7682, -2236.6274,-1751.2744,482.7777, -2232.8083,-1746.7634,480.8852, -2232.8083,-1746.7634,480.8852}}
};

// sistema de congelar o player //
new timer_congelado[MAX_PLAYERS] = {-1, ...};
new congelado[MAX_PLAYERS];





new Rank[][ranks] =
{
	{"Tidak Ada", 19783, 0xffffffff},
	{"Perak 1", 19783, 0xffffffff},
	{"Perak 2", 19784, 0xffffffff},
	{"Perak 3", 19778, 0xffffffff},
	{"Perak 4", 19785, 0xffffffff},
	{"Emas 1", 19783, 0xffff00ff},
	{"Emas 2", 19784, 0xffff00ff},
	{"Emas 3", 19778, 0xffff00ff},
	{"Emas 4", 19785, 0xffff00ff},
	{"Emas 5", 19781, 0xffff00ff},
	{"Platina 1", 19783, 0x00ffffff},
	{"Platina 2", 19784, 0x00ffffff},
	{"Platina 3", 19778, 0x00ffffff},
	{"Platina 4", 19785, 0x00ffffff},
	{"Platina 5", 19781, 0x00ffffff},
    {"Platina 6", 19779, 0x00ffffff},
	{"Zamrud 1", 19783, 0x00ff00ff},
	{"Zamrud 2", 19784, 0x00ff00ff},
	{"Zamrud 3", 19778, 0x00ff00ff},
	{"Zamrud 4", 19785, 0x00ff00ff},
	{"Zamrud 5", 19781, 0x00ff00ff},
    {"Zamrud 6", 19779, 0x00ff00ff},
    {"Zamrud 7", 19782, 0x00ff00ff},
	{"Berlian 1", 19783, 0xff00ffff},
	{"Berlian 2", 19784, 0xff00ffff},
	{"Berlian 3", 19778, 0xff00ffff},
	{"Berlian 4", 19785, 0xff00ffff},
	{"Berlian 5", 19781, 0xff00ffff},
    {"Berlian 6", 19779, 0xff00ffff},
    {"Berlian 7", 19782, 0xff00ffff},
	{"Berlian 8", 19780, 0xff00ffff},
	{"Master",     19780, 0xff00ffff}
};


// lanterna //
new lanterna_player[MAX_PLAYERS];


// sistema tv de espionar //
new tv_player[MAX_PLAYERS];
new mostrando_tv[MAX_PLAYERS];



new Teleportes[][teles] =
{
	{"Kantor Polisi LS", 1539.2112,-1658.0586,13.5469, 0, 0},
	{"Menara Parasut LS",  1544.4380,-1353.4886,329.4740, 0, 0},
	{"Taman Gleen LS",  1935.6510,-1185.1389,20.0234, 0, 0},
	{"Morro LS",  2164.6189,-1011.3820,62.8007, 0, 0},
	{"Tempat Lobby", 248.3148,302.1143,999.1484, 1, 999},
	{"Tempat Pesawat", 1.6880,28.0373,1199.5938, 1, 999}
};



// logs //
new LogBase[MAX_BASES][50][300];
new LogCombates[50][300];
new LogKill[50][300];
new LogBan[50][300];
new LogKick[50][300];
new LogGmx[50][300];
new LogAdmin[50][300];
new LogPunicao[50][300];
new LogCash[50][300];
new LogNick[50][300];
new LogConecoes[50][300];



new Bau[MAX_BAUS][bauss];


new Explosivo[MAX_EXPLOSIVOS][explo];
new lista_explosivos[MAX_PLAYERS][MAX_EXPLOSIVOS];



//  lista de Itens dropar //
new LootAleatorio_0[][] =
{
    {82, 3}, // minuman sprite
    {124, 3}, // minuman energy
    {124, 3}, // minuman energy
    {28, 1}, // kotak jus apel
    {28, 1}, // kotak jus apel
    {29, 1}, // kotak jus jeruk
    {30, 1}, // kotak susu
    {31, 1}, // hotdog
    {31, 1}, // hotdog
	{13, 1}, // rompi lvl 1
	{16, 1}, // helm lvl 1
	{2, 1}, // obat sakit (painkiller)
	{2, 1}, // obat sakit (painkiller)
	{3, 1}, // repair kit
	{3, 1}, // repair kit
	{4, 1}, // masker
	{5, 150}, // uang
	{5, 150}, // uang
	{6, 1}, // botol kosong
	{6, 1}, // botol kosong
	{7, 1}, // korek api
	{7, 1}, // korek api
	{7, 1}, // korek api
	{8, 1}, // medkit
	{8, 1}, // medkit
	{9, 1}, // galon kosong
	{9, 1}, // galon kosong
	{9, 1}, // galon kosong
	{10, 1}, // galon isi
	{11, 1}, // api unggun
	{11, 1}, // api unggun
	{20, 1}, // stik golf
	{20, 1}, // stik golf
	{22, 1}, // pisau
	{22, 1}, // pisau
	{23, 1}, // tongkat baseball
	{23, 1}, // tongkat baseball
	{24, 1}, // sekop
	{24, 1}, // sekop
	{25, 1}, // stik biliar
	{25, 1}, // stik biliar
	{56, 20}, // rokok
	{56, 20}, // rokok
	{56, 20}, // rokok
	{62, 20}, // peluru pistol
	{67, 10}, // bubuk mesiu
	{68, 1}, // botol berisi air
	{69, 1}, // daging mentah
	{70, 1}, // daging matang
	{70, 1}, // daging matang
	{71, 1}, // panci
	{71, 1}, // panci
	{72, 1}, // bubuk kopi
	{72, 1}, // bubuk kopi
	{73, 1}, // gelas kopi
	{73, 1}, // gelas kopi
	{74, 3}, // roti
	{74, 3}, // roti
	{75, 2}, // hamburger
	{75, 2}, // hamburger
	{76, 3}, // jeruk
	{76, 3}, // jeruk
	{77, 4}, // apel merah
	{77, 4}, // apel merah
	{78, 2}, // part pistol
	{79, 1}, // part shotgun
	{80, 1}, // part submachine
	{84, 1}, // aki soak
	{84, 1}, // aki soak
	{86, 1}, // ban bocor
	{86, 1}, // ban bocor
	{86, 1}, // ban bocor
	{86, 1}, // ban bocor
	{87, 1}, // toolbox
	{87, 1}, // toolbox
	{88, 1}, // mesin rusak
	{88, 1}, // mesin rusak
	{90, 5}, // besi bekas
	{109, 3}, // pisang
	{109, 3}, // pisang
	{110, 3}, // apel hijau
	{110, 3}  // apel hijau
};




//  daftar item loot //
new LootAleatorio_1[][] =
{
    {82, 3}, // minuman sprite
    {124, 5}, // minuman energetico
    {124, 5}, // minuman energetico
    {33, 1}, // senter
    {28, 3}, // jus apel
    {28, 3}, // jus apel
    {29, 3}, // jus jeruk
    {29, 3}, // jus jeruk
    {30, 3}, // susu kotak
    {30, 3}, // susu kotak
    {31, 3}, // hotdog
    {31, 3}, // hotdog
    {32, 1}, // paha ayam
    {14, 1}, // rompi level 2
    {17, 1}, // helm level 2
    {4, 1}, // masker
    {90, 10}, // scrap
    {90, 10}, // scrap
    {78, 3}, // fragmen pistol
    {79, 2}, // fragmen shotgun
    {80, 2}, // fragmen smg
    {81, 1}, // fragmen rifle
    {34, 1}, // granat
    {35, 1}, // granat gas
    {36, 1}, // molotov
    {10, 1}, // jerigen penuh
    {10, 1}, // jerigen penuh
    {100, 1}, // radio
    {107, 1}, // peta
    {107, 1}, // peta
    {108, 1}, // gps
    {108, 1}, // gps
    {67, 25}, // bubuk mesiu
    {67, 25}, // bubuk mesiu
    {109, 4}, // pisang
    {109, 4}, // pisang
    {110, 5}, // apel hijau
    {110, 5}, // apel hijau
    {89, 1}, // mesin bagus
    {85, 1}, // ban bagus
    {83, 1}, // aki terisi
    {87, 1}, // kotak alat
    {87, 1}, // kotak alat
    {87, 1}, // kotak alat
    {71, 1}, // panci
    {91, 5}, // sampah
    {92, 5}, // sampah
    {93, 5}, // sampah
    {94, 5}, // sampah
    {95, 5}, // sampah
    {62, 25}, // peluru pistol
    {62, 25}  // peluru pistol
};



// daftar item loot //
new LootAleatorio_2[][] =
{
    {131, 1}, // ranjau darat
    {82, 3}, // sprite
    {124, 7}, // minuman energetico
    {124, 7}, // minuman energetico
    {33, 1}, // senter
    {32, 3}, // paha ayam
    {90, 20}, // scrap
    {26, 1}, // katana
    {34, 1}, // granat
    {36, 1}, // molotov
    {10, 1}, // jerigen penuh
    {15, 1}, // rompi level 3
    {18, 1}, // helm level 3
    {2, 3}, // analgesik
    {2, 3}, // analgesik
    {3, 3}, // perbaikan
    {3, 3}, // perbaikan
    {8, 3}, // kotak pertolongan pertama
    {8, 3}, // kotak pertolongan pertama
    {8, 3}, // kotak pertolongan pertama
    {5, 1000}, // uang
    {4, 1}, // masker
    {62, 30}, // peluru pistol
    {63, 15}, // peluru shotgun
    {64, 30}, // peluru submachine gun
    {96, 15}, // kayu
    {96, 15}, // kayu
    {97, 5}, // logam
    {97, 5}, // logam
    {98, 10}, // batu
    {98, 10}, // batu
    {100, 1}, // radio
    {107, 1}, // peta
    {107, 1}, // peta
    {108, 1}, // gps
    {108, 1}, // gps
    {67, 50}, // bubuk mesiu
    {67, 50}, // bubuk mesiu
    {111, 1}, // kotak apel
    {112, 1}, // kotak apel hijau
    {113, 1}, // kotak jeruk
    {54, 1}, // bahan peledak C4
    {55, 1}, // detonator
    {87, 1}, // kotak alat
    {87, 1}, // kotak alat
    {87, 1} // kotak alat
};


// recompenssas de nivel //
new Recompensas[][] =
{
    {1, 5, 500, 0},
	{2, 100, 1, 0},
	{3, 5, 1500, 0},
	{4, 108, 1, 0},
	{5, 2, 5, 0},
	{6, 5, 3000, 0},
	{7, 107, 1, 0},
	{8, 15, 1, 100},
	{9, 8, 5, 0},
	{10, 18, 1, 100},
	{11, 5, 5000, 0},
	{12, 67, 100, 0},
	{13, 96, 100, 0},
	{14, 97, 100, 0},
	{15, 98, 100, 0},
	{16, 5, 7500, 0},
	{17, 26, 1, 8},
	{18, 113, 1, 0},
	{19, 44, 1, 29},
	{20, 46, 1, 31},
	{21, 103, 1, 0},
	{22, 5, 10000, 0},
	{23, 67, 150, 0},
	{24, 96, 150, 0},
	{25, 97, 150, 0},
	{26, 98, 150, 0},
    {27, 79, 10, 0},
    {28, 54, 5, 0},
    {29, 55, 1, 0},
    {30, 5, 15000, 0}
};


new mostrando_premios[MAX_PLAYERS];




new Itens[][info_itens] = //
{
	{0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0xffffffff, 0xffffffff, 0, 0, 0, "Kosong", 0, "Slot Kosong."},
	{1, 0.0, 0.0, 0.0, 0.0, 0.0, 147.0, 0.8, 0xffffffff, 0xffffffff, 1, 1886, 0, "Kamera Keamanan", 1, "Digunakan di markas, kamu bisa melihat kamera dari mana saja di peta."},
	{1, 0.0, 0.0, 0.0,  322.0, 0.0, 31.0, 0.7, 0xffffffff, 0xffffffff, 2, 11748, 0, "Obat Penghilang Nyeri", 1, "Saat digunakan, mengembalikan 25% HP."},
	{1, 0.12, 0.0, 0.0, 338.0, 0.0, 170.0, 0.7, 0xffffffff, 0xffffffff, 3, 19921, 0, "Perbaikan Peralatan", 1, "Memperbaiki 20% helm dan rompi kamu."},
	{1, 0.1, 0.0, 0.0, 0.0, 0.0, 90.0, 0.9, 0xffffffff, 0xffffffff, 4, 19472, 300, "Masker Gas", 0, "Masker ini melindungi kamu dari area hijau di peta yang mengandung gas beracun."},
	{1, 0.1, 0.0, 0.0, 310.0, 0.0, 305.0, 0.8, 0xffffffff, 0xffffffff, 5, 1212, 0, "Uang", 1, "Saat digunakan, menambahkan uang ke saldo kamu yang ada di kanan bawah di bawah material."},
	{1,  0.20, 0.0, 0.0, 310.0, 0.0, 305.0, 0.8, 0xffffffff, 0xffffffff, 6, 19570, 0, "Botol Kosong", 0, "Item ini digunakan di pantai dan sungai untuk mengisi dengan air."},
	{1, 0.1, 0.0, 0.0, 310.0, 0.0, 305.0, 0.8, 0xffffffff, 0xffffffff, 7, 19998, 0, "Pemantik Api", 0, "Digunakan untuk menyalakan api unggun."},
	{1, 0.1, 0.0, 0.0, 310.0, 0.0, 305.0, 0.8, 0xffffffff, 0xffffffff, 8, 11738, 0, "Kotak P3K", 1, "Saat digunakan, mengembalikan 50% HP."},
	{1, 0.23, 0.0, 0.0, 310.0, 0.0, 305.0, 0.8, 0xffffffff, 0xffffffff, 9, 1650, 0, "Ember Bensin Kosong", 0, "Item ini digunakan di SPBU untuk mengambil bahan bakar."},
	{1, 0.23, 0.0, 0.0, 310.0, 0.0, 305.0, 0.8, 0xffffffff, 0xffffffff, 10, 1650, 0, "Ember Bensin Penuh", 0, "Item ini digunakan untuk mengisi bahan bakar kendaraan."},
	{1, 0.15, 0.0, 0.0, 310.0, 0.0, 305.0, 0.8, 0xffffffff, 0xffffffff, 11, 19632, 0, "Api Unggun", 0, "Item ini membuat api unggun di tanah, kamu bisa memasak makanan dengan bahan yang diperlukan."},
	{1, 0.2, 0.0, 90.0, 335.0, 0.0, 323.0, 1.7, 0xffffffff, 0xffffffff, 12, 370, 0, "JetPack", 0, "Item langka, bisa digunakan di luar pertempuran jika baterai terisi."},
	{1, 0.2, 90.0, 0.0, 180.0, 90.0, 0.0, 0.7, 0xffffffff, 0xffffffff, 13, 19142, 100, "Rompi Lv 1", 0, "Melindungi kamu dari damage yang diterima di rompi."},
	{1, 0.2, 90.0, 0.0, 180.0, 90.0, 0.0, 0.7, 0xffffffff, 0xffffffff, 14, 19142, 100, "Rompi Lv 2", 0, "Melindungi kamu dan mengurangi 50% damage yang diterima di rompi."},
	{1, 0.2, 90.0, 0.0, 180.0, 90.0, 0.0, 0.7, 0xffffffff, 0xffffffff, 15, 19142, 100, "Rompi Lv 3", 0, "Melindungi kamu dan mengurangi 70% damage yang diterima di rompi."},
	{1, 0.2, 0.0, -90.0, 180.0, 90.0, 0.0, 0.7, 0xffffffff, 0xffffffff, 16, 19141, 100, "Helm Lv 1", 0, "Melindungi kamu dari damage yang diterima di helm."},
	{1, 0.2, 0.0, -90.0, 180.0, 90.0, 0.0, 0.7, 0xffffffff, 0xffffffff, 17, 19141, 100, "Helm Lv 2", 0, "Melindungi kamu dan mengurangi 50% damage yang diterima di helm."},
	{1, 0.2, 0.0, -90.0, 180.0, 90.0, 0.0, 0.7, 0xffffffff, 0xffffffff, 18, 19141, 100, "Helm Lv 3", 0, "Melindungi kamu dan mengurangi 70% damage yang diterima di helm."},

	// Senjata
	{1,  0.15, 90.0, 0.0, 63.0, 90.0, 0.0, 0.55, 0xffffffff, 0xffffffff, 19, 331, 1, "Tinju Inggris", 0, "Senjata tangan buat gebukin orang."},
	{1,  0.15, 90.0, 0.0, 120.0, 346.0, 0.0, 0.72, 0xffffffff, 0xffffffff, 20, 333, 2, "Stik Golf", 0, "Bisa buat main golf atau jadi pentungan."},
	{1,  0.15, 90.0, 0.0, 59.0, 145.0, 0.0, 1.26, 0xffffffff, 0xffffffff, 21, 334, 3, "Pentung Polisi", 0, "Biasa dipake polisi, tapi bisa buat jaga diri."},
	{1,  0.15, 90.0, 0.0, 59.0, 145.0, 0.0, 0.9, 0xffffffff, 0xffffffff, 22, 335, 4, "Pisau", 0, "Senjata tajam buat tusuk atau potong."},
	{1,  0.15, 90.0, 0.0, 280.0, 339.0, 329.0, 1.87, 0xffffffff, 0xffffffff, 23, 336, 5, "Tongkat Baseball", 0, "Bisa buat senjata."},
	{1,  0.15, 90.0, 90.0, 292.0, 327.0, 45.0, 2.52, 0xffffffff, 0xffffffff, 24, 337, 6, "Sekop", 0, "Biasa buat gali kubur, tapi bisa jadi senjata juga."},
	{1,  0.15, 90.0, 0.0, 53.0, 324.0, 0.0, 1.08, 0xffffffff, 0xffffffff, 25, 338, 7, "Tongkat Biliar", 0, "Buat main pool atau jadi pentungan."},
	{1,  0.15, 90.0, 0.0, 53.0, 324.0, 0.0, 1.08, 0xffffffff, 0xffffffff, 26, 339, 8, "Katana", 0, "Pedang samurai tajam buat tebas musuh."},
	{1,  0.15, 90.0, 0.0, 344.0, 0.0, 75.0, 2.07, 0xffffffff, 0xffffffff, 27, 341, 9, "Gergaji Mesin", 0, "Buat motong kayu... atau manusia."},
	{1,  0.15, 90.0, 0.0, 341.0, 0.0, 141.0, 1.04, 0xffffffff, 0xffffffff, 28, 19564, TIPO_BEBIDA, "Jus Apel", 1, "Minuman sehat, nambah +8 HP."},
	{1,  0.15, 90.0, 0.0, 341.0, 0.0, 141.0, 1.04, 0xffffffff, 0xffffffff, 29, 19563, TIPO_BEBIDA, "Jus Jeruk", 1, "Segar banget, nambah +8 HP."},
	{1,  0.15, 90.0, 0.0, 341.0, 0.0, 141.0, 1.04, 0xffffffff, 0xffffffff, 30, 19569, TIPO_BEBIDA, "Susu Sapi", 1, "Bikin kuat, nambah +8 HP."},
	{1,  0.15, 90.0, 0.0, 282.0, 0.0, 0.0, 0.74, 0xffffffff, 0xffffffff, 31, 2769, TIPO_COMIDA, "Hotdog", 1, "Makanan cepat saji, nambah +13 HP."},
	{1,  0.15, 90.0, 0.0, 21.0, 110.0, 144.0, 1.09, 0xffffffff, 0xffffffff, 32, 19847, TIPO_COMIDA, "Paha Ayam", 1, "Enak buat dimakan, nambah +20 HP."},
	{1,  0.15, 90.0, 0.0, 121.0, 29.0, 0.0, 0.54, 0xffffffff, 0xffffffff, 33, 18641, 1, "Senter", 1, "Buat nerangin tempat gelap."},
	{1,  0.15, 90.0, 0.0, 180.0, 166.0, 62.0, 0.30, 0xffffffff, 0xffffffff, 34, 342, 16, "Granat", 1, "Ledakan gede, bahaya banget!"},
	{1,  0.15, 90.0, 0.0, 180.0, 166.0, 229.0, 0.64, 0xffffffff, 0xffffffff, 35, 343, 17, "Gas Air Mata", 0, "Bikin mata perih, visi berkurang."},
	{1,  0.15, 90.0, 0.0, 180.0, 166.0, 229.0, 0.88, 0xffffffff, 0xffffffff, 36, 344, 18, "Molotov", 0, "Bom bakar, bikin area kebakar."},
	{1,  0.15, 90.0, 0.0, 0.0, 17.0, 56.0, 0.82, 0xffffffff, 0xffffffff, 37, 346, 22, "Pistol 9mm", 0, "Senjata standar, cocok buat berantem."},
	{1,  0.15, 90.0, 0.0, 0.0, 17.0, 56.0, 1.18, 0xffffffff, 0xffffffff, 38, 347, 23, "Pistol 9mm (Silencer)", 0, "Pistol senyap, musuh ga denger."},
	{1,  0.15, 90.0, 0.0, 0.0, 17.0, 72.0, 0.98, 0xffffffff, 0xffffffff, 39, 348, 24, "Desert Eagle", 0, "Pistol gede, damage gila-gilaan!"},
	{1,  0.15, 90.0, 0.0, 353.0, 0.0, 83.0, 1.67, 0xffffffff, 0xffffffff, 40, 349, 25, "Shotgun", 0, "Senjata jarak dekat, damage tinggi."},
	{1,  0.15, 90.0, 0.0, 353.0, 0.0, 74.0, 1.39, 0xffffffff, 0xffffffff, 41, 350, 26, "Double Barrel Shotgun", 0, "Shotgun dua laras, tembak dua kali."},
	{1,  0.15, 90.0, 0.0, 353.0, 0.0, 74.0, 1.86, 0xffffffff, 0xffffffff, 42, 351, 27, "Combat Shotgun", 0, "Shotgun semi-otomatis, tembak cepat."},
	{1,  0.15, 90.0, 0.0, 353.0, 0.0, 0.0, 0.90, 0xffffffff, 0xffffffff, 43, 352, 28, "Uzi", 0, "Senapan kecil, tembakan cepat banget."},
	{1,  0.15, 90.0, 0.0, 337.0, 0.0, 70.0, 1.31, 0xffffffff, 0xffffffff, 44, 353, 29, "MP5", 0, "Senapan presisi, stabil dan akurat."},
	{1,  0.15, 90.0, 0.0, 358.0, 0.0, 79.0, 1.88, 0xffffffff, 0xffffffff, 45, 355, 30, "AK-47", 0, "Senjata perang, damage tinggi banget."},
	{1,  0.15, 90.0, 0.0, 358.0, 0.0, 79.0, 1.88, 0xffffffff, 0xffffffff, 46, 356, 31, "M16", 0, "Senapan otomatis, akurat dan mematikan."},
	{1,  0.15, 90.0, 0.0, 358.0, 0.0, 63.0, 1.14, 0xffffffff, 0xffffffff, 47, 372, 32, "TEC-9", 0, "Pistol otomatis, tembakan cepat."},
	{1,  0.15, 90.0, 0.0, 350.0, 0.0, 81.0, 1.67, 0xffffffff, 0xffffffff, 48, 357, 33, "Sniper Rifle", 0, "Tembak dari jauh, satu tembakan satu nyawa."},
	{1,  0.15, 90.0, 0.0, 344.0, 0.0, 84.0, 1.56, 0xffffffff, 0xffffffff, 49, 358, 34, "M24 Sniper", 0, "Sniper jarak jauh, presisi tinggi."},
	{1,  0.15, 90.0, 0.0, 346.0, 0.0, 73.0, 1.56, 0xffffffff, 0xffffffff, 50, 359, 35, "RPG", 0, "Peluncur rudal, hancurin semuanya!"},
	{1,  0.15, 90.0, 0.0, 346.0, 0.0, 73.0, 1.56, 0xffffffff, 0xffffffff, 51, 360, 36, "Roket Heat-Seeker", 0, "Rudal ngejar target, bahaya banget!"},
	{1,  0.15, 90.0, 0.0, 346.0, 0.0, 80.0, 2.58, 0xffffffff, 0xffffffff, 52, 361, 37, "Flamethrower", 0, "Senjata api, bakar semua yang lewat!"},
	{1,  0.15, 90.0, 0.0, 346.0, 0.0, 80.0, 2.72, 0xffffffff, 0xffffffff, 53, 362, 38, "Minigun", 0, "Senjata berat, tembakan super cepat!"},
	{1,  0.10, 90.0, 0.0, -20.0, 0.0, 138.0, 0.76, 0xffffffff, 0xffffffff, 54, 1654, 0, "Bom C4", 1, "Bom jarak jauh, bisa hancurin bangunan, gerbang, atau musuh."},
	{1,  0.15, 90.0, 0.0, 310.0, 0.0, 305.0, 0.88, 0xffffffff, 0xffffffff, 55, 364, 40, "Detonator", 0, "Pemicu bom C4."},
	{1,  0.15, 90.0, 0.0, 310.0, 0.0, 305.0, 0.52, 0xffffffff, 0xffffffff, 56, 19897, 0, "Rokok", 1, "Ngerokok bikin dingin & ngantuk berkurang, tapi nyawa berkurang pelan-pelan. Butuh korek buat nyalain."},
	{1,  0.15, 90.0, 0.0, 18.0, 0.0, 68.0, 1.75, 0xffffffff, 0xffffffff, 57, 366, 42, "Pemadam Api", 0, "Buat padamin kebakaran."},
	{1,  0.15, 90.0, 0.0, 346.0, 0.0, 56.0, 0.87, 0xffffffff, 0xffffffff, 58, 367, 43, "Kamera", 0, "Mau foto-foto dulu?"},
	{1,  0.15, 90.0, 0.0, 1.0, 270.0, 63.0, 0.52, 0xffffffff, 0xffffffff, 59, 368, 44, "Kacamata Malam", 0, "Bisa liat jelas di tempat gelap."},
	{1,  0.15, 90.0, 0.0, 1.0, 270.0, 63.0, 0.52, 0xffffffff, 0xffffffff, 60, 369, 45, "Kacamata Termal", 0, "Bisa deteksi panas, cocok buat berburu."},
	{1,  0.15, 90.0, 0.0, 0.00, 0.00, 0.00, 1.20, 0xffffffff, 0xffffffff, 61, 371, 46, "Parasut", 0, "Buat terjun dari tempat tinggi."},

	// municoes
	{0,  0.15, 0.0, 0.0, 345.0, 0.0, 19.0, 0.90, 0xffffffff, 0xffffffff, 62, 2040, 2, "Ammo 9mm", 1, "Isi ulang untuk pistol 9mm."},
	{0,  0.15, 0.0, 0.0, 345.0, 0.0, 19.0, 0.90, 0xffffffff, 0xffffffff, 63, 2040, 3, "Ammo Kaliber 12", 1, "Isi ulang untuk shotgun."},
	{0,  0.15, 0.0, 0.0, 345.0, 0.0, 19.0, 0.90, 0xffffffff, 0xffffffff, 64, 2040, 4, "Ammo SMG", 1, "Isi ulang untuk senapan kecil/submachine gun."},
	{0,  0.15, 0.0, 0.0, 345.0, 0.0, 19.0, 0.90, 0xffffffff, 0xffffffff, 65, 2040, 5, "Ammo 5.56", 1, "Isi ulang untuk AK-47 & M16."},
	{0,  0.15, 0.0, 0.0, 345.0, 0.0, 19.0, 0.90, 0xffffffff, 0xffffffff, 66, 2040, 6, "Ammo 7.62x51", 1, "Isi ulang untuk sniper jarak menengah/jauh."},

	// lanjut //
	{0,  0.15, 0.0, 0.0, 345.0, 0.0, 19.0, 0.90, 0xffffffff, 0xffffffff, 67, 2037, 0, "Bubuk Mesiu", 1, "Didapetin dari ngebunuh Zombie, dipakai buat bikin peluru dan item lain di Meja Crafting."},
	{1,  0.20, 0.0, 0.0, 310.0, 0.0, 305.0, 0.8, 0xffffffff, 0xffffffff, 68, 19570, TIPO_BEBIDA, "Botol Air", 0, "Nambah +8 darah pas diminum."},
	{0,  0.1,  0.0, 0.0, 345.0, 0.0, 19.0, 0.90, 0xffffffff, 0xffffffff, 69, 19582, 0, "Daging Mentah", 1, "Dipakai di api unggun buat dimasak."},
	{0,  0.1,  0.0, 0.0, 345.0, 0.0, 19.0, 0.90, 0xffffffff, 0xffffffff, 70, 19882, TIPO_COMIDA, "Daging Matang", 1, "Nambah +15 darah pas dimakan."},
	{1,  0.15, 0.0, 0.0, 330.0, 0.0, 164.0, 1.18, 0xffffffff, 0xffffffff, 71, 19584, 0, "Panci", 0, "Dipakai di api unggun buat masak kalau punya bahan-bahannya."},
	{0,  0.1,  0.0, 0.0, 330.0, 0.0, 164.0, 1.18, 0xffffffff, 0xffffffff, 72, 19573, 0, "Bubuk Kopi", 0, "Dipakai di api unggun buat bikin kopi."},
	{0,  0.1,  0.0, 0.0, 330.0, 0.0, 164.0, 0.85, 0xffffffff, 0xffffffff, 73, 19835, TIPO_BEBIDA, "Cangkir Kopi", 0, "Nambah +8 darah pas diminum."},
	{0,  0.1,  0.0, 0.0, 330.0, 0.0, 164.0, 0.85, 0xffffffff, 0xffffffff, 74, 11740, TIPO_COMIDA, "Roti", 0, "Nambah +15 darah pas dimakan."},
	{0, 0.1,-25.0,-90.0, 138.0, 0.0, 294.0, 1.18, 0xffffffff, 0xffffffff, 75, 2880, TIPO_COMIDA, "Burger", 0, "Nambah +15 darah pas dimakan."},
	{0,  0.1,  0.0, 0.0, 0.000, 0.0, 0.000, 0.60, 0xffffffff, 0xffffffff, 76, 19574, TIPO_COMIDA, "Jeruk", 1, "Nambah +15 darah pas dimakan."},
	{0,  0.1,  0.0, 0.0, 0.000, 0.0, 0.000, 0.60, 0xffffffff, 0xffffffff, 77, 19575, TIPO_COMIDA, "Apel", 1, "Nambah +15 darah pas dimakan."},

	// potongan senjata //
	{1,  0.1,  0.0, 0.0, 0.0, 248.0, 110.0, 0.85, 0xffffffff, 0xffffffff, 78, 19773, 0, "Potongan Pistol", 1, "Bisa dipakai di Pasar Gelap buat bikin pistol."},
	{1,  0.1,  0.0, 0.0, 91.0,  0.0,   0.0, 0.85, 0xffffffff, 0xffffffff, 79, 2034,  0, "Potongan Shotgun", 1, "Bisa dipakai di Pasar Gelap buat bikin senjata shotgun."},
	{1,  0.1,  0.0, 0.0, 91.0,  0.0,   0.0, 0.85, 0xffffffff, 0xffffffff, 80, 2044,  0, "Potongan Sub", 1, "Bisa dipakai di Pasar Gelap buat bikin senjata submachine."},
	{1,  0.1,  0.0, 0.0, 94.0, 69.0,  0.0,  0.71, 0xffffffff, 0xffffffff, 81, 2035,  0, "Potongan Rifle", 1, "Bisa dipakai di Pasar Gelap buat bikin AK-47 atau M16."},

	// bebida ( fragmento de sniper removido ) //
	{1,  0.1,  0.0, 0.0, 94.0, 69.0,  0.0,  0.71, 0xffffffff, 0xffffffff, 82, 1546,  TIPO_BEBIDA, "Sprite", 1, "Menambahkan +8 ke kesehatanmu saat meminum item ini."},

	// untuk kendaraan //
	{1,  0.15, 0.0, 0.0, 337.0, 0.0, 35.0, 0.91, 0xffffffff, 0xffffffff, 83, 19918, 0, "Baterai Terisi", 0, "Digunakan di kendaraan untuk mengganti baterai kosong atau saat merakit kendaraan."},
	{1,  0.15, 0.0, 0.0, 337.0, 0.0, 35.0, 0.91, 0xffffffff, 0xffffffff, 84, 19918, 0, "Baterai Kosong", 0, "Bisa diisi ulang di bengkel."},
	{1,  0.46, 0.0, 0.0, 0.0, 0.0, 31.0, 1.13, 0xffffffff, 0xffffffff, 85, 1025, 0, "Ban Bagus", 0, "Digunakan di kendaraan untuk mengganti ban bocor atau saat merakit kendaraan."},
	{1,  0.46, 0.0, 0.0, 0.0, 0.0, 31.0, 1.13, 0xffffffff, 0xffffffff, 86, 1025, 0, "Ban Bocor", 0, "Bisa diperbaiki di bengkel."},
	{1,  0.20, 0.0, 0.0, 337.0, 0.0, 31.0, 0.86, 0xffffffff, 0xffffffff, 87, 2969, 0, "Kotak Alat", 0, "Dipakai untuk memperbaiki kendaraan atau saat merakit kendaraan."},
	{1,  0.10, 0.0, 0.0, 337.0, 0.0, 31.0, 0.97, 0xffffffff, 0xffffffff, 88, 19917, 0, "Mesin Rusak", 0, "Bisa diperbaiki di bengkel."},
	{1,  0.10, 0.0, 0.0, 337.0, 0.0, 31.0, 0.97, 0xffffffff, 0xffffffff, 89, 19917, 0, "Mesin Bagus", 0, "Digunakan saat merakit kendaraan."},

	// untuk barang bekas dan barang daur ulang //
	{0,  0.10, 0.0, 0.0, 337.0, 0.0, 31.0, 0.97, 0xffffffff, 0xffffffff, 90, 1579, 0, "Barang Bekas", 1, "Digunakan di Meja Craft untuk bikin berbagai item dengan bahan lain."},
	{1,  0.10, 0.0, 0.0, 337.0, 0.0, 31.0, 0.97, 0xffffffff, 0xffffffff, 91, 3106, TIPO_SUCATA, "Bola Biliar 8", 1, "Bisa didaur ulang di Mesin Daur Ulang buat dapetin barang bekas."},
	{1,  0.10, 0.0, 0.0, 337.0, 0.0, 31.0, 0.97, 0xffffffff, 0xffffffff, 92, 11750, TIPO_SUCATA, "Borgol Rusak", 1, "Bisa didaur ulang di Mesin Daur Ulang buat dapetin barang bekas."},
	{1,  0.10, 0.0, 0.0, 337.0, 0.0, 31.0, 0.97, 0xffffffff, 0xffffffff, 93, 11747, TIPO_SUCATA, "Gulungan Perban", 1, "Bisa didaur ulang di Mesin Daur Ulang buat dapetin barang bekas."},
	{1,  0.10, 0.0, 0.0, 337.0, 0.0, 31.0, 0.97, 0xffffffff, 0xffffffff, 94, 19995, TIPO_SUCATA, "Peluru Bekas", 1, "Bisa didaur ulang di Mesin Daur Ulang buat dapetin barang bekas."},
	{1,  0.10, 0.0, 0.0, 337.0, 0.0, 31.0, 0.97, 0xffffffff, 0xffffffff, 95, 19513, TIPO_SUCATA, "HP Rusak", 1, "Bisa didaur ulang di Mesin Daur Ulang buat dapetin barang bekas."},

	// untuk material //
	{0,  0.15, 0.0, 0.0, 337.0, 0.0, 31.0, 0.97, 0xffffffff, 0xffffffff, 96, 19793, 0, "Kayu", 1, "Kalau digunakan, kayu akan ditambah di sisi kanan layar."},
	{0,  0.15, 0.0, 0.0, 337.0, 0.0, 31.0, 0.97, 0xffffffff, 0xffffffff, 97, 19941, 0, "Logam", 1, "Kalau digunakan, logam akan ditambah di sisi kanan layar."},
	{0,  0.15, 0.0, 0.0, 337.0, 0.0, 31.0, 0.97, 0xffffffff, 0xffffffff, 98, 3930, 0, "Batu", 1, "Kalau digunakan, batu akan ditambah di sisi kanan layar."},

	// lainnya //
	{0,  0.15, 0.0, 90.0, 337.0, 0.0, 31.0, 0.97, 0xffffffff, 0xffffffff, 99, 1275, TIPO_SKIN, "Skin", 0, "Digunakan untuk mengganti skin karakter kamu di mode cerita."},
	{1,  0.15, 0.0, 90.0, 91.0, 27.0, 0.0, 0.75, 0xffffffff, 0xffffffff, 100, 2967, 0, "Radio Komunikasi", 100, "Alat buat nyambung ke channel suara VoIP, nelpon kontak, dan pakai /g (chat global)."},
	{0,  0.20, 0.0, 00.0, 91.0, 27.0, 0.0, 0.99, 0xffffffff, 0xffffffff, 101, 1271, 0, "Kotak Barang", 1, "Tempat nyimpen sampai 50 item, cuma pemiliknya yang bisa akses."},
	{0,  0.10, 90.0, 0.0, 0.00, 0.00, 59.00, 1.0, 0xffffffff, 0xffffffff, 102, 980, 0, "Gerbang Besar", 1, "Gerbang elektrik, bisa dibuka pakai tombol H atau klakson kendaraan, anggota markas juga bisa akses."},
	{0,  0.10, 0.0, 90.0, 0.00, 0.00, 39.00, 1.0, 0xffffffff, 0xffffffff, 103, 2930, 0, "Gerbang Kecil", 1, "Gerbang elektrik, bisa dibuka pakai tombol H, anggota markas juga bisa akses."},
	{0,  0.15, -90.0, 0.0, 0.0, 0.0, 220.0, 1.0, 0xffffffff, 0xffffffff, 104, 1248, 0, "Kendaraan Inventaris", 0, "Kendaraan portabel, gak butuh bensin atau baterai."},
	{0,  0.15, -90.0, 0.0, 0.0, 0.0, 220.0, 1.0, 0xffffffff, 0xffffffff, 105, 1248, 465, "Heli-Drone", 0, "Kendaraan mini yang dikendalikan jarak menengah, cocok buat intai wilayah tanpa ketahuan."},
	{0,  0.15, -90.0, 0.0, 0.0, 0.0, 220.0, 1.0, 0xffffffff, 0xffffffff, 106, 1248, 441, "Mobil RC", 0, "Kendaraan mini yang dikendalikan jarak menengah, cocok buat intai wilayah tanpa ketahuan."},
	{1,  0.1, 0.0, 0.0, 90.0, 0.0, 0.0, 0.9, 0xffffffff, 0xffffffff, 107, 19167, 0, "Peta", 0, "Peta yang nunjukin semua kota dan lokasi penting, kamu bisa pakai /mapa juga."},
	{1,  0.1, 0.0, 0.0, 90.0, 0.0, 0.0, 0.9, 0xffffffff, 0xffffffff, 108, 18875, 0, "GPS", 0, "Alat yang ngasih tampilan radar dan peta sementara, kamu juga bisa pakai /gps."},
	{0,  0.1, 0.0, 0.0, 90.0, 0.0, 0.0, 0.76, 0xffffffff, 0xffffffff, 109, 19578, TIPO_COMIDA, "Pisang", 1, "Nambahin +15 darah kalau dimakan."},

    {0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.60, 0xffffffff, 0xffffffff, 110, 19576, TIPO_COMIDA, "Apel Hijau", 1, "Mengembalikan +15 darah saat kamu makan item ini."},

	{0, 0.20, 0.0, 0.0, 341.0, 0.0, 0.0, 0.95, 0xffffffff, 0xffffffff, 111, 19636, 0, "Kotak Apel", 0, "Berisi 10 apel yang akan jatuh di dekat kamu."},
	{0, 0.20, 0.0, 0.0, 341.0, 0.0, 0.0, 0.95, 0xffffffff, 0xffffffff, 112, 19637, 0, "Kotak Apel Hijau", 0, "Berisi 10 apel hijau yang akan jatuh di dekat kamu."},
	{0, 0.20, 0.0, 0.0, 341.0, 0.0, 0.0, 0.95, 0xffffffff, 0xffffffff, 113, 19638, 0, "Kotak Jeruk", 0, "Berisi 10 jeruk yang akan jatuh di dekat kamu."},
	{0, 0.10, 0.0, 0.0, 0.0, 0.0, 152.0, 0.63, 0xffffffff, 0xffffffff, 114, 19893, 0, "NotBook", 0, "Alat portabel dengan fitur berguna, termasuk tampilan satelit."},

	{0, 0.10, 0.0, 0.0, 0.0, 0.0, 152.0, 0.63, 0xffffffff, 0xffffffff, 115, 365, TIPO_TINTA, "Cat Hijau", 0, "Digunakan untuk mengecat kendaraan jadi hijau."},
	{0, 0.10, 0.0, 0.0, 0.0, 0.0, 152.0, 0.63, 0xffffffff, 0xffffffff, 116, 365, TIPO_TINTA, "Cat Kuning", 0, "Digunakan untuk mengecat kendaraan jadi kuning."},
	{0, 0.10, 0.0, 0.0, 0.0, 0.0, 152.0, 0.63, 0xffffffff, 0xffffffff, 117, 365, TIPO_TINTA, "Cat Merah", 0, "Digunakan untuk mengecat kendaraan jadi merah."},
	{0, 0.10, 0.0, 0.0, 0.0, 0.0, 152.0, 0.63, 0xffffffff, 0xffffffff, 118, 365, TIPO_TINTA, "Cat Biru", 0, "Digunakan untuk mengecat kendaraan jadi biru."},
	{0, 0.10, 0.0, 0.0, 0.0, 0.0, 152.0, 0.63, 0xffffffff, 0xffffffff, 119, 365, TIPO_TINTA, "Cat Hitam", 0, "Digunakan untuk mengecat kendaraan jadi hitam."},
	{0, 0.10, 0.0, 0.0, 0.0, 0.0, 152.0, 0.63, 0xffffffff, 0xffffffff, 120, 365, TIPO_TINTA, "Cat Putih", 0, "Digunakan untuk mengecat kendaraan jadi putih."},
	{0, 0.10, 0.0, 0.0, 0.0, 0.0, 152.0, 0.63, 0xffffffff, 0xffffffff, 121, 365, TIPO_TINTA, "Cat Pink", 0, "Digunakan untuk mengecat kendaraan jadi pink."},
	{0, 0.10, 0.0, 0.0, 0.0, 0.0, 152.0, 0.63, 0xffffffff, 0xffffffff, 122, 365, TIPO_TINTA, "Cat Abu-Abu", 0, "Digunakan untuk mengecat kendaraan jadi abu-abu."},
	{0, 0.10, 0.0, 0.0, 0.0, 0.0, 152.0, 0.63, 0xffffffff, 0xffffffff, 123, 365, TIPO_TINTA, "Cat Cyan", 0, "Digunakan untuk mengecat kendaraan jadi cyan."},
	{0, 0.10, 0.0, 0.0, 0.0, 0.0, 152.0, 0.63, 0xffffffff, 0xffffffff, 124, 2958, 0, "Energi Drink", 0, "Ngurangin rasa haus 20 poin dan kantuk 25 poin."},
	{0, 0.15, -90.0, 0.0, 0.0, 0.0, 220.0, 1.0, 0xffffffff, 0xffffffff, 125, 1248, 481, "BMX", 0, "Sepeda BMX dari inventori, nggak bisa dipakai buat perang."},
	{0, 0.15, -90.0, 0.0, 0.0, 0.0, 220.0, 1.0, 0xffffffff, 0xffffffff, 126, 1248, 510, "Sepeda Gunung", 0, "Sepeda gunung dari inventori, nggak bisa dipakai buat perang."},
	{0, 0.15, -90.0, 0.0, 0.0, 0.0, 220.0, 1.0, 0xffffffff, 0xffffffff, 127, 1581, 0, "Ganti Nama", 0, "Digunakan buat ganti nama kamu di game."},
	{1, 0.05, -90.0, 0.0, 0.0, 0.0, 220.0, 1.0, 0xffffffff, 0xffffffff, 128, 19804, 1, "Gembok", 0, "Digunakan bareng item Kunci buat ngunci kendaraan kamu, pakai item ini deket kendaraan pribadi kamu."},
	{1, 0.05, -90.0, 0.0, 0.0, 0.0, 220.0, 1.0, 0xffffffff, 0xffffffff, 129, 11746, 1, "Kunci", 0, "Digunakan bareng item Gembok buat ngunci kendaraan kamu, pakai item ini deket kendaraan pribadi kamu."},
	{1, 0.1, 0.0, 0.0, 90.0, 0.0, 0.0, 0.9, 0xffffffff, 0xffffffff, 130, 1247, 0, "SEASON PASS", 0, "Season Pass ini bikin kamu bisa ambil hadiah-hadiah keren dari pass."},
	{1, 0.1, 0.0, 0.0, 90.0, 0.0, 0.0, 0.9, 0xffffffff, 0xffffffff, 131, MINA, 0, "Ranjau Darat", 1, "Perangkap yang meledak kalau ditembak atau didekati pemain, efeknya radius 10 meter."}
	//19167
};






new Tutorial[][tuto] =
{
	{0, 999, 1466.7473, -1681.7118, 24.5479, 1433.3564, -1624.5806, 33.3848, 1488.0031, -1639.7725, 14.1484, 20000, 0, "SELAMAT DATANG", "Selamat datang di DAYZI, kami harap Anda memiliki pengalaman bermain yang luar biasa. Sebelum memulai Mode Cerita Anda, kami akan menjelaskan sedikit tentang beberapa sistem penting."},

	{0, 999, 1344.6368,-1625.6517,13.5918, 1342.6989,-1625.0349,13.5806, 1342.4027,-1622.7043,13.0852, 20000, 0, "Lapar & Haus", "Kami memiliki sistem lapar dan haus yang berbeda dari kebanyakan. Semakin kecil rasa lapar dan hausmu, semakin baik. Hindari memiliki lebih dari 75 poin lapar atau haus, atau kamu akan mulai kehilangan nyawa secara perlahan. Kamu bisa makan dan minum item yang kamu temukan di sekitar peta. Disarankan untuk membawa sebotol air di inventarismu."},

	{0, 999, 141.6120,-893.6676,8.1105, 141.9023,-891.6594,8.4826, 111.3142,-891.6875,-0.4917, 20000, 16, "Dingin", "Jika kamu berada terlalu lama di dalam air atau hujan, tingkat dinginmu akan meningkat, hindari memiliki lebih dari 75 dingin, karena kamu akan mulai kehilangan darah secara perlahan. Tingkat dinginmu akan berkurang saat berada di dekat api unggun atau di dalam kendaraan."},

	{0, 999, -66.7278,-1137.9574, 2.0781, -67.8054,-1136.0098,1.0781, -72.8245,-1138.8743,1.07805, 20000, 0, "TIDUR", "Seperti di kehidupan nyata, kamu akan merasa mengantuk seiring berjalannya waktu. Kamu bisa beristirahat di dalam kendaraan sebagai penumpang, atau gunakan tempat tidur. Tempat tidur dibangun di dalam base, jadi usahakan memulai dengan item ini saat kamu membuat base. Jika kamu terlalu mengantuk, kamu bisa pingsan selama beberapa detik."},

	{0, 999, -63.65398, -1128.28333, 0.75079, -63.65398, -1128.28333, 0.75079, -62.90970, -1127.92822, 0.14330, 20000, 0, "NYAWA DAN PERALATAN", "Bar Merah, Putih, dan Biru mewakili Nyawa, Armor, dan Helm kamu. Kamu bisa memulihkan nyawa dengan menggunakan Kit Medis, pereda nyeri, atau dengan makan dan minum sesuatu."},

	{0, 999, -41.52227, -1158.43457, 0.84906, -41.52227, -1158.43457, 0.84906, -40.97532, -1159.27954, 0.16900, 20000, 0, "ARMOR DAN HELM", "Armor dan Helm melindungi kamu dari kerusakan yang diterima. Tergantung pada level peralatan, daya tahannya akan jauh lebih besar dan kerusakan yang diterima akan berkurang. Peralatan ini bisa dipulihkan sebagian dengan alat perbaikan peralatan."},

	{0, 999, -44.33275, -1157.25989, 0.22581, -44.33275, -1157.25989, 0.22581, -44.61800, -1158.04834, 0.15800, 20000, 0, "MASKER GAS", "Masker gas melindungi kamu dari kerusakan yang terjadi di area hijau di peta, tempat gas beracun berada. Kamu bisa memakai masker gas, dan itu hanya akan terpakai ketika kamu memasuki area hijau tersebut."},

	{0, 999, 211.53406, 1807.31946, 52.18054, 211.53406, 1807.31946, 52.18054, 147.59071, 1891.63367, 17.35527, 20000, 0, "AREA HIJAU(Green zone)", "Area hijau di peta mengandung kualitas loot yang lebih baik, hindari memasuki area ini jika kamu tidak memakai masker gas. Terkadang hanya masker gas tidak cukup, jadi pastikan kamu selalu siap."},

	{0, 999, 224.17662, 1834.74194, 12.64649, 224.71960, 1835.32935, 12.64649, 225.60529, 1833.77112, 11.73980, 20000, 0, "SENJATA DAN AMUNISI", "Kamu bisa membawa 3 senjata yang terpasang, yang bisa diakses menggunakan tombol Y di luar kendaraan. Kamu akan membutuhkan amunisi untuk senjatamu dan ada 5 jenis amunisi: pistol, kaliber 12, submachine gun, rifle, dan sniper."},

	{1, 999, 292.2806,-32.1206,1002.0156, 295.5131,-32.0828,1002.0156, 293.3734,-30.7042,1001.5156, 20000, 0,"FRAGMENTASI SENJATA", "Fragmen-fragmen ini dapat ditemukan di peta, dan juga bisa dibuat di meja kerajinan dengan bahan-bahan yang diperlukan. Mereka digunakan untuk merakit berbagai jenis senjata di pasar gelap."},

	{1, 999, 299.2401,-38.6304,1002.5156, 293.0068,-32.7475,1002.5156, 295.0352,-40.2165,1001.5156, 20000, 0, "PASAR GELAP", "Ditemukan di peta, tempat-tempat ini menawarkan daftar berbagai item dan peralatan yang dapat dibeli dengan uang Anda, selain merakit senjata dari fragmen, yang cukup ada di inventaris Anda."},

	{0, 999, 555.85156, 1519.41443, 1.62837, 555.85156, 1519.41443, 1.62837, 557.27374, 1518.70020, 0.91576, 20000, 0, "MATERIAL PEMBANGUNAN", "Material-material ini adalah Kayu, Batu, Logam, dan Bubuk Mesiu, dengan material-material ini Anda dapat memetakan basis Anda, dan juga dapat membangun item di meja kerajinan, beberapa membutuhkan pemotongan."},

	{0, 999, -1095.2245,-1632.7679,76.3672, -1086.9303,-1637.8303,76.3672, -1111.2986,-1638.4806,76.3672, 20000, 0, "BASIS", "Kamu bisa bangun basis sendiri, atau gabung ke basis orang lain. Setiap basis bisa menampung 20 anggota, ada saluran VOIP buat anggota, bisa maping atau edit objek di basis, dan kamu bisa ganti nama basis kalau kamu yang punya."},

	{0, 999, -1106.0704,-1637.3448,76.3672, -1110.6823,-1640.0507,76.3672, -1116.29773, -1636.44104, 75.39520, 20000, 0, "OBJEK UNTUK BASIS", "Kamu bisa maping basis pakai berbagai objek dari daftar, ada yang bisa diinteraksiin kayak kursi, tempat tidur, lampu, JBL, dan ada juga yang cuma buat maping doang, kayak dinding kayu. Setiap objek butuh beberapa material buat dibangun."},

	{0, 999, -1106.0704,-1637.3448,77.3672, -1106.0704,-1637.3448,76.8672, -1104.07471, -1639.11353, 76.14480, 20000, 0, "MESIN DAUR ULANG", "Dengan mesin daur ulang, kamu bisa dapetin Scrap, yang penting buat crafting. Kamu harus daur ulang barang buat dapetin material ini, mesin daur ulang gampang banget dipake dan cuma bisa dipake sama pemiliknya."},

	{0, 999, -1111.6245,-1637.9818,77.8672, -1106.0704,-1637.3448,77.8672, -1107.49500, -1635.27869, 75.37500, 20000, 0, "MEJA CRAFTING", "Dengan meja crafting, kamu bisa bikin banyak barang, kayak rompi, helm, MedKit, obat nyeri, dll. Setiap barang butuh beberapa material, dan barang yang kamu buat masuk ke inventaris yang bisa diakses pake tombol N kalau lagi gak di kendaraan."},

	{0, 999, -1082.95227, -1640.97400, 77.41428, -1082.95227, -1640.97400, 76.41428, -1076.7863, -1638.4641, 76.2488, 20000, 0, "KENDARAAN", "Kendaraan bisa ditemukan di peta dan gak bisa dipake sebelum dirakit. Buat rakit kendaraan, kamu butuh komponen kayak: kotak alat, mesin, baterai, dan ban. Setelah kendaraan kamu dirakit, kamu bisa akses beberapa fungsi kendaraan lewat /carmenu."},

	{0, 999, -1095.0930,-1610.0049,77.3739, -1095.0930,-1610.0049,76.3739, -1098.24890, -1613.08289, 75.35090, 20000, 0, "KOMPONEN KENDARAAN", "Kamu bisa nemuin komponen-komponen ini di peta, dan bisa benerin di bengkel supaya bisa dipake lagi. Sebaiknya bawa ban yang bagus di inventaris kalau mau keluar pake kendaraan, soalnya gak tau kapan ban bisa bocor."},

	{0, 0, 215.7005,-142.9807,2.0197, 213.2267,-146.1900,1.6237, 204.2671,-146.1017,1.6237, 20000, 0, "BENGKEL", "Bengkel bisa kamu temuin lewat peta, di situ kamu bisa benerin komponen kendaraan atau kendaraan kamu sendiri. Cukup pake /menu atau klakson di lokasi. Buat benerin komponen, kamu harus jalan ke ikon yang ada di dalam bengkel."},

	{0, 999, -2246.7551,-2542.3887,31.7943, -2243.6838,-2548.0981,31.9059, -2242.6064,-2559.9790,31.9219, 20000, 0, "STASIUN PENGISIAN BAHAN BAKAR", "Temuin di peta, pake galon kosong di pom bensin, kamu dapet 20 liter yang bisa dipake buat isi tangki kendaraan, atau cukup bawa galon itu di inventaris buat dipake kapan aja. Ini satu-satunya cara buat isi bahan bakar kendaraan."},

	{0, 999, 263.90588, 1883.94507, -29.79210, 263.26065, 1884.67139, -29.79210, 263.10800, 1883.41406, -30.34392, 20000, 0, "GPS", "Item ini bisa kamu temuin di peta, gunanya buat ngeliat radar kamu sementara waktu sampe baterainya abis. Buat pake lagi, tunggu baterainya terisi. Jangan pake item ini kalau kamu mau diem, soalnya bisa bikin kamu kekurangan di situasi tertentu."},

	{0, 999, 1433.3564, -1624.5806, 33.3848, 1466.7473, -1681.7118, 24.5479, 1488.0031, -1639.7725, 14.1484, 15000, 0, "SELESAI TUTORIAL", "Kalau ada yang bingung soal sistem atau apa aja, tinggal pake /ajuda kapan aja. Di sana kamu bakal nemuin banyak info berguna dan belajar banyak hal baru."}
};
new tutorial[MAX_PLAYERS];
new timer_tutorial[MAX_PLAYERS] = {-1, ...};
new timer_tutorial2[MAX_PLAYERS] = {-1, ...};

new carro_tutorial;

// laptop //


new mostrando_laptop[MAX_PLAYERS];
new olhando_satelite[MAX_PLAYERS];
new actor_player[MAX_PLAYERS];
new Float:satelite_player[MAX_PLAYERS][3];
new timer_satelite[MAX_PLAYERS] = {-1, ...};
new pode_mecher[MAX_PLAYERS];

new hackeando_id[MAX_PLAYERS];
new hackeando_tempo[MAX_PLAYERS];



new ArmasCostas[][armsco] =
{
    {2, 333, 0, 1, 0.047999, -0.088999, 0.254000, 0.000000, -139.300033, 0.000000, 1.000000, 1.000000, 1.000000},
	{3, 334, 0, 7, 0.118000, 0.064000, -0.038999, -82.300010, 136.799987, 0.000000, 1.000000, 1.000000, 1.000000},
	{4, 335, 0, 7, 0.218000, 0.112999, -0.017000, -76.500007, 104.399986, 0.000000, 1.000000, 1.000000, 1.000000},
	{5, 336, 0, 1, -0.078000, -0.124000, -0.173000, -13.499999, -49.499996, 0.000000, 1.000000, 1.000000, 1.000000},
	{6,337, 0, 1, -0.097999, -0.021000, -0.137000, -14.600002, -43.399997, -91.100006, 1.000000, 1.000000, 1.000000},
	{7,338, 0, 1, -0.097999, -0.021000, -0.137000, -14.600002, -43.399997, -91.100006, 1.000000, 1.000000, 1.000000},
	{8,339, 0, 1, -0.097999, -0.021000, -0.137000, -14.600002, -43.399997, -91.100006, 1.000000, 1.000000, 1.000000},
	{9,341, 0, 1, -0.526999, -0.125999, -0.192999, 0.000000, -18.600002, 0.000000, 1.000000, 1.000000, 1.000000},
	{22,346, 0, 8, 0.184000, -0.030000, 0.105999, -99.599975, 0.000000, -5.600002, 1.000000, 1.000000, 1.000000},
	{23,347, 0, 8, 0.184000, -0.030000, 0.105999, -99.599975, 0.000000, -5.600002, 1.000000, 1.000000, 1.000000},
	{24,348, 0, 8, 0.184000, -0.030000, 0.105999, -99.599975, 0.000000, -5.600002, 1.000000, 1.000000, 1.000000},
	{25,349, 0, 1, 0.108999, -0.123999, 0.175000, 0.000000, 170.699951, 8.399999, 1.000000, 1.000000, 1.000000},
	{26,350, 0, 1, 0.073999, -0.123999, 0.071000, 0.000000, 152.600036, 0.000000, 1.000000, 1.000000, 1.000000},
	{27,351, 0, 1, 0.205000, -0.183000, 0.194999, 0.000000, -173.499969, 15.499999, 1.000000, 1.000000, 1.000000},
	{28,352, 0, 1, -0.136000, -0.118000, -0.080000, 0.000000, 137.900070, 11.500000, 1.000000, 1.000000, 1.000000},
	{29,353, 0, 1, -0.084999, -0.132999, 0.000000, 0.000000, 169.800048, 11.700001, 1.000000, 1.000000, 1.000000},
	{32,372, 0, 1, -0.355000, -0.138999, -0.016999, -4.100024, 44.199985, 9.299999, 1.000000, 1.000000, 1.000000},
	{30,355, 0, 1, -0.094000, -0.107000, -0.095999, 171.000015, 42.300006, 9.800000, 1.000000, 1.000000, 1.000000},
	{31,356, 0, 1, -0.094000, -0.107000, -0.095999, 171.000015, 42.300006, 9.800000, 1.000000, 1.000000, 1.000000},
	{33,357, 0, 1, -0.186999, -0.133999, 0.081999, 0.000000, 47.899997, 3.600001, 1.000000, 1.000000, 1.000000},
	{34,358, 0, 1, -0.186999, -0.133999, 0.081999, 0.000000, 47.899997, 3.600001, 1.000000, 1.000000, 1.000000}
};



////// sistema de clima ////
new id_clima_server;
new proximo_clima_server;
new clima_server;
new tempo_clima = 120;
enum clims
{
    clima_Temperatura,
	clima_Nome[100],
	clima_Clima,
	clima_Duracao
};
new Clima[][clims] =
{
	{3,  "Cerah", 0, 60*25}, 					// 25 menit
	{-2, "Berawan", 7, 60*15}, 					// 15 menit
	{0,  "Badai Pasir", 19, 60*5}, 				// 5 menit
	{-3, "Hujan", 16, 60*5}, 					// 5 menit
	{-2, "Kabut Tebal", 9, 60*10}, 				// 10 menit
	{-5, "Hujan Deras", 8, 60*3},               // 3 menit
	{-2, "Cuaca Buruk", 20, 60*20}				// 20 menit
};


// classes //

new mostrando_classes[MAX_PLAYERS];
new id_classe[MAX_PLAYERS];





new Classes[][clas] =
{
	{ 0x7FFFD4ff, "Penjelajah", 250, 55, 3, "Memiliki banyak keterampilan dengan senjata tajam, dan dalam mendapatkan material craft dalam waktu yang lebih singkat.", "Mendapatkan lebih banyak kayu dan dalam waktu yang lebih singkat saat menebang pohon.", "Mendapatkan lebih banyak batu dalam waktu yang lebih singkat saat memecah batu.", "Peluang lebih besar untuk mendapatkan logam saat memecah batu.", "Kerusakan senjata tajam meningkat 100%", "Setiap senjata memberikan dua kali lipat kerusakan ke Zombie."},
	{ 0xFFB6C1ff, "Dokter", 70, 141, 5, "Keterampilan dengan penyembuhan dan pengurangan waktu penggunaan Item penyembuhan.", "Menyembuhkan 1 HP setiap 1 menit.", "Waktu penggunaan Kit Medis dan Analgesik dikurangi setengahnya.", "Tidak perlu Kit Medis untuk menyelamatkan pemain yang terluka.", "Menerima lebih banyak kerusakan dari Zombie.", "Menerima lebih sedikit kerusakan dari senjata tajam."},
	{ 0xF0E68Cff, "Montir", 50, 148, 10, "Keterampilan dalam memperbaiki kendaraan dan suku cadang, konsumsi berkurang, dan daya tahan lebih lama.", "Memperbaiki kendaraan tanpa perlu Kotak Alat, gunakan /reparar.", "Menggunakan lebih sedikit Bensin dan Baterai saat mengendarai kendaraan.", "Mengisi bensin dua kali lipat saat menggunakan jerigen.", "Mengurangi waktu untuk memperbaiki suku cadang kendaraan.", "Peluang untuk merusak Ban berkurang secara signifikan."},
	{ 0xFF8C00ff, "Pemburu", 285, 93, 15, "Keterampilan lebih tinggi dengan Senapan dan Pistol, pemburu zombie yang hebat.", "Kerusakan M16 atau AK47 meningkat 25%.", "Kerusakan Pistol meningkat 50%.", "Menerima setengah kerusakan dari Pistol, selama dilengkapi dengan Pistol juga.", "Mendapatkan Amunisi Senapan saat membunuh Zombie.", "Membunuh Zombie dengan 1 tembakan ke kepala."},
	{ 0xD8BFD8ff, "Teroris", 210, 224, 20, "Keterampilan dan Kerusakan dari bahan peledak C-4 yang ditingkatkan.", "Menerima 70% lebih sedikit kerusakan dari bahan peledak C-4.", "Saat meledakkan C-4, menyebabkan 100% lebih banyak kerusakan.", "Dapat menempatkan hingga 5 bahan peledak C-4.", "_", "_"}
};




new ClasseBase[][classbas] =
{
	{0xa1a1a1ff, "Sederhana", 1},
	{0x6495EDff, "Militer", 5},
	{0x9ACD32ff, "Teroris", 10}
};




new JBL[MAX_JBL][jbls];
new jbl_player[MAX_PLAYERS];



new Drop[MAX_DROPS][drops];
new Float:PosDrop[][] =
{
	{2634.2046,-2504.0330,13.4922,89.5867},
	{2714.7778,-1600.2233,13.0331,168.4012},
	{1963.2563,-1143.4078,25.9725,177.3208},
	{1495.6493,-1646.2247,14.0469,156.8496},
	{2041.6622,-2199.0962,13.5469,60.4882},
	{1114.9069,-2022.6290,74.4297,331.4381},
	{832.2205,-2025.8573,12.8672,331.5843},
	{747.9012,-1173.2380,21.1397,30.0737},
	{677.4614,-523.0510,16.1836,353.2254},
	{339.6635,-134.5110,1.5781,48.6441},
	{1365.5885,296.9248,19.4063,69.5541},
	{2540.9954,43.2710,26.3437,69.5541},
	{2743.3206,-537.7306,49.2930,290.7879},
	{2497.8340,648.3036,10.8203,299.4151},
	{1697.0530,1591.2502,10.8203,41.2592},
	{-78.6301,1159.8621,19.7422,292.5426},
	{-321.0596,1519.2421,75.3570,331.7305},
	{318.4473,2001.4656,17.6406,82.5679},
	{38.2869,1738.2617,17.6406,356.5885},
	{-1.5897,2294.8953,24.4190,332.0229},
	{-839.6908,1490.7958,18.1343,356.4423},
	{-1424.3052,2595.1309,55.7193,10.0411},
	{-2294.7842,2422.5007,4.9141,42.2102},
	{-2570.2852,2471.6704,19.7880,152.3141},
	{-2693.7078,2262.8818,56.1706,183.8984},
	{-2347.7664,1546.4490,26.0469,279.2363},
	{-2132.0000,561.5618,35.0156,279.2363},
	{-1999.7640,214.8495,27.6875,177.7596},
	{-1822.7028,-568.9172,16.3359,177.6134},
	{-2201.4302,-2474.6331,30.4688,191.2122}
};
new proximo_drop = 1800;
new PosDropUsada[MAX_DROPS];

// Kendaraan Inv, drone, mainan dll ///
new RC[MAX_PLAYERS];
new Float:VidaRC[MAX_PLAYERS];

// cadeiras kursi//
new cadeira_player[MAX_PLAYERS];

// camas kamera//
new cama_player[MAX_PLAYERS];

// new aviao pesawat pas login//
new pickup_paraquedas;
new pickup_sair_aviao;


// voip  voice //
new SV_LSTREAM:lstream[MAX_PLAYERS] = { SV_NULL, ... };


// sistema de radio //
new Contatos[MAX_PLAYERS][MAX_CONTATOS][MAX_PLAYER_NAME];
new Canal_Player[MAX_PLAYERS];
new Canal_Base_Player[MAX_PLAYERS];
new Canal_Privado[MAX_PLAYERS];
new SV_GSTREAM:CanalPrivado[MAX_PLAYERS];

new chamando[MAX_PLAYERS];
new timer_chamando[MAX_PLAYERS] = {-1, ...};
new tempo_chamando[MAX_PLAYERS];
new mostrando_chamada[MAX_PLAYERS];




new Radios[][rad] =
{
	{SV_NULL, "Los Santos",   1603.5365,  -1512.4199, 28.5859, 2000.0},
	{SV_NULL, "Las Venturas", 1782.0000,  1738.4082,  6.7587,  2000.0},
	{SV_NULL, "San Fierro",  -2202.0000,  506.7520,   35.0156, 2000.0}
};







new Menu[MAX_PLAYERS][MAX_MENU][menuu];

new mostrando_menu[MAX_PLAYERS];
new menu_id[MAX_PLAYERS];
new max_menu[MAX_PLAYERS];
new escolhendo_menu[MAX_PLAYERS];
new pagina_menu[MAX_PLAYERS];
new nome_menu[MAX_PLAYERS][100];
new botao_menu[MAX_PLAYERS][100];


// LOJA CASH //

new mostrando_item_cash[MAX_PLAYERS];






new pagina_loja_cash[MAX_PLAYERS];
new id_loja_cash[MAX_PLAYERS];
new mostrando_loja_cash[MAX_PLAYERS];

new Items_Loja_Cash[][] =
{
	{130, 1, 30000}, // PASSE //
	{128, 1, 2500}, // cadeado //
	{129, 1, 2500}, // chave //
	{12, 1, 10000}, // jetpack //
	{114, 1, 20000}, // notbook //
	{125, 1, 8000}, // bmx //
	{126, 1, 10000}, // montain bike //
	{1, 1, 2500}, // camera de seguranca //
	{105, 1, 50000}, // heli-drone //
	{106, 1, 5000},  // carrinho //
	{115, 1, 1000},  // lata de tinta //
	{116, 1, 1000},  // lata de tinta //
	{117, 1, 1000},  // lata de tinta //
	{118, 1, 1000},  // lata de tinta //
	{119, 1, 1000},  // lata de tinta //
	{120, 1, 1000},  // lata de tinta //
	{121, 1, 1000},  // lata de tinta //
	{122, 1, 1000},  // lata de tinta //
	{123, 1, 1000}   // lata de tinta //
};


// menssagens aleatorias //
new Menssagems[][] =
{
	"Masuk ke server Discord kami: https://discord.gg/AGtxRSPt",
	"Masuk ke server Discord kami: https://discord.gg/AGtxRSPt",
	"Gunakan '/creditos'"
};

new tempo_menssagem[MAX_PLAYERS];

// creditos //
new Creditos[][] =
{
	"\n{00ffff}KREDIT UNTUK SERVER\n\n\n",
	"{a1a1a1}Bocoran script ini: JoaoKristani\n",
	"{ffff00}Scripter {ffffff}Pembuat Game Mode dan Pemetaan.\n\n",
	"{ffffff}Terima kasih kepada {00ff00}Victor {ffffff}karena telah menyediakan {00ffff}VPS {ffffff}dengan kualitas terbaik {a1a1a1}[ {ffff00}RAZE HOST {a1a1a1}].\n\n",
	"{ffffff}Selamat untuk tim {00ffff}Staff {ffffff}atas dedikasi luar biasa mereka untuk para pemain.\n\n",
	"{a1a1a1}Terima kasih kepada Forum Samp dan para pembuat Plugin serta Include berikut:\n",
	"Streamer, ZCMD, SSCANF, DOF2, ColAndreas, YSF, SampVoice.\n\n"
};



// ajuda bases //
new ajuda_base[][] =
{
	"\n{00ffff}BANTUAN TENTANG BASES\n\n\n",
	"{ffffff}Ketika mencapai Level {00ffff}3 {ffffff}anda dapat membuat sebuah Basis dengan perintah {a1a1a1}/criarbase{ffffff}, basis\n",
	"{ffffff}anda dapat memiliki maksimal {ffff00}20 {ffffff}anggota.\n\n",
	"{ffffff}Jika anda adalah Pemilik, atau bagian dari daftar anggota sebuah basis, setiap kali anda kembali\n",
	"{ffffff}ke menu setelah mati, anda akan muncul di lokasi Basis anda, gunakan\n",
	"{ffffff}perintah {ffff00}/base {ffffff}untuk membuka menu, atau mencari lokasi Basis anda, dalam menu ini anda bisa mengakses\n",
	"{ffffff}beberapa informasi, seperti daftar anggota, objek yang ditempatkan di basis, Log dan banyak lagi.\n\n",
	"{ffffff}Anda bisa memetakan basis anda jika memiliki bahan yang diperlukan untuk membuat setiap objek, gunakan\n",
	"{ffffff}opsi {00ff00}Pemetaan {ffffff}di menu ini.\n\n",
	"{ffffff}Pemilik basis bisa mengubah Nama Basis, mengubah Kelas basis, menghapus anggota, memberikan\n",
	"{ffffff}kepemilikan, menerima permintaan dan banyak opsi lainnya.\n",
	"{ffffff}Ketika anggota terakhir meninggalkan basis, basis tersebut akan dihancurkan secara otomatis.\n\n"
};


// ajuda haid //
new ajuda_haid[][] =
{
	"\n{00ffff}BANTUAN TENTANG RAID / INVASI\n\n\n",
	"{ffff00}JAM OPERASIONAL:\n",
	"{ffffff}Jumat dan Sabtu: 19:00 hingga 22:00\n",
	"{ffffff}Minggu: 16:00 hingga 19:00\n",
	"{a1a1a1}Tidak akan memungkinkan menggunakan C-4 atau detonator di luar jam tersebut.\n\n"
};


// ajuda bases //
// bantuan tentang pintu bagasi kendaraan //
new ajuda_portamalas[][] =
{
	"\n{00ffff}BANTUAN TENTANG PINTU BAGASI KENDARAAN\n\n\n",
	"{ffffff}Sistem {ffff00}Pintu Bagasi {ffffff}hanya tersedia untuk kendaraan pribadi, yaitu kendaraan yang\n",
	"{ffffff}terdaftar dan muncul di {a1a1a1}/carmenu{ffffff}, pintu bagasi hanya bisa digunakan ketika\n",
	"{ffffff}kendaraan tidak terkunci.\n\n",
	"{ffff00}MENYIMPAN ATAU MENGAMBIL ITEM:\n",
	"{ffffff}Untuk menyimpan atau mengambil item, kamu harus berada dekat dengan Pintu Bagasi kendaraan dan membukanya\n",
	"{ffffff}menggunakan tombol {00ffff}H{ffffff}, lalu pilih opsi yang diinginkan. Jika memilih menyimpan, inventarimu akan terbuka\n",
	"{ffffff}dan tinggal klik dua kali untuk menyimpan. Jika memilih mengambil, pintu bagasi akan terbuka di sebelah kiri\n",
	"{ffffff}layar, dan tinggal klik dua kali pada item yang ingin kamu ambil dari pintu bagasi.\n\n"
};



// bantuan tentang kendaraan //
new ajuda_veiculos[][] =
{
	"\n{00ffff}BANTUAN TENTANG KENDARAAN\n\n\n",
	"{ffffff}Kamu bisa merakit sebuah {00ff00}Kendaraan{ffffff} jika memiliki bagian dan alat yang diperlukan, kendaraan ini\n",
	"{ffffff}dapat ditemukan di peta, dan tidak bisa digunakan sampai selesai dirakit.\n\n",
	"{ffffff}Setelah merakit kendaraanmu, kamu bisa mengakses {ffff00}Menu{ffffff}, dengan menggunakan perintah {ffff00}/carmenu{ffffff}, di mana\n",
	"{ffffff}kamu akan menemukan beberapa opsi seperti: mengunci, memarkir, menyalakan atau mematikan mesin, lampu, dll.\n\n",
	"{ffffff}Kamu hanya bisa memiliki satu Kendaraan di server, setelah logout kendaraanmu tidak akan tersimpan di\n",
	"{ffffff}server, dan hanya akan kembali ketika kamu login kembali, dan kendaraan tersebut akan ditemukan\n",
	"{ffffff}di tempat terakhir kali kamu parkir melalui menu /carmenu.\n\n",
	"{ffffff}Kamu bisa menggunakan perintah {00ffff}/ajudaveiculos {ffffff}untuk mengakses perintah-perintah kendaraanmu.\n\n"
};



// respawn otomatis //
new ajuda_respawn[][] =
{
	"\n{00ffff}BANTUAN TENTANG RESPAWN OTOMATIS\n\n\n",
	"{ffffff}Setelah waktu yang ditentukan, server akan melakukan respawn pada beberapa sistem, perhatikan\n",
	"{ffffff}Textdraw di sudut kiri bawah layar kamu yang menampilkan waktu untuk respawn berikutnya, dan\n",
	"{ffffff}pastikan untuk tidak melewatkan item yang ada di tanah, atau merasa dirugikan dengan cara apapun.\n\n",
	"{ffff00}POHON: {ffffff}Semua Pohon di server akan direspawn, dan siap untuk ditebang kembali.\n",
	"{ffff00}BATU: {ffffff}Semua Batu di server akan direspawn, dan siap untuk dihancurkan kembali.\n",
	"{ffff00}SPBU: {ffffff}Semua Tempat Pengisian Bensin di SPBU akan terisi 100% kembali.\n",
	"{ffff00}API: {ffffff}Semua Api di server akan dihancurkan.\n",
	"{ffff00}AIR DROPS: {ffffff}Semua Air Drops yang jatuh di Peta akan dihancurkan.\n",
	"{ffff00}ZOMBIE: {ffffff}Semua Zombie akan direspawn dan siap untuk menyerang atau diserang.\n",
	"{ffff00}LOOT CHEST: {ffffff}Semua Loot Chest akan dipulihkan dengan item acak.\n",
	"{ffff00}ITEM DI TANAH: {ffffff}Semua item yang dijatuhkan di tanah akan dihancurkan secara permanen.\n\n"
};


// peralatan dan material //
new ajuda_equipamentos_e_materiais[][] =
{
	"\n{00ffff}BANTUAN TENTANG PERALATAN DAN MATERIAL\n\n\n",
	"{ffff00}SENJATA:\n",
	"{ffffff}Kamu bisa memiliki hingga {00ff00}3{ffffff} Senjata yang dipasang di karakter kamu, senjata dan amunisi ini bisa\n",
	"{ffffff}diakses dengan menekan tombol {ffff00}Y{ffffff} saat berjalan.\n\n",
	"{ffff00}PERALATAN:\n",
	"{ffffff}Rompi melindungi kamu dari kerusakan yang diterima dari senjata pada dada dan punggung, Helm melindungi kamu\n",
	"{ffffff}dari kerusakan yang diterima dari senjata pada kepala, dan Masker melindungi kamu dari kerusakan\n",
	"{ffffff}di {00ff00}Area hijau{ffffff} pada peta, tempat di mana loot terbaik dapat ditemukan.\n\n",
	"{ffff00}MATERIAL:\n",
	"{ffffff}Material yang kamu dapatkan dengan menebang pohon, menghancurkan batu, atau membunuh Zombie\n",
	"{ffffff}dapat dijatuhkan dengan perintah {00ff00}/dropar{ffffff}, mereka dapat dilihat di bagian kanan atas\n",
	"{ffffff}di bawah bar kesehatan, rompi, dan helm. Material ini digunakan untuk membuat kerajinan barang dan\n",
	"{ffffff}objek untuk basis kamu, dan disarankan untuk menyimpan material ini di {ffff00}Loot Chest{ffffff} pada basis\n",
	"{ffffff}untuk menghindari kehilangan material jika kamu mati.\n\n",
	"{FF0000}PERHATIAN:\n",
	"{ffffff}Jika kamu mati dengan cara apapun di Mode Cerita, senjata, amunisi, peralatan, dan material kamu akan dijatuhkan di tempat\n",
	"{ffffff}tersebut, dan siapa saja bisa mengambil item tersebut. Namun, apa yang ada di inventaris kamu tidak akan dijatuhkan,\n",
	"{ffffff}jadi kamu tidak perlu khawatir.\n\n"
};


// bantuan tentang zombie //
new ajuda_zombies[][] =
{
	"\n{00ffff}BANTUAN TENTANG ZOMBIES\n\n\n",
	"{ffffff}Saat berjalan-jalan, kamu bisa bertemu dengan seorang {00ffff}Zombie{ffffff}, beberapa di antaranya bisa membawa peralatan\n",
	"{ffffff}seperti Rompi, Helm, Masker, dan Senjata Tangan. Setelah mengalahkan Zombie, dia akan menjatuhkan di tanah\n",
	"{ffffff}peralatan dan senjata yang dia gunakan, serta sejumlah Bubuk Mesiu, yang sangat\n",
	"{ffffff}penting untuk pembuatan objek dan item di basis.\n\n",
	"{ffffff}Berhati-hatilah agar tidak terkena serangan dari makhluk ini, karena setiap pukulan bisa mengurangi {ff0000}20 Kesehatan{ffffff}, dan jika\n",
	"{ffffff}kamu mati, peralatan, senjata, dan material kamu akan dijatuhkan di tempat kejadian, dan kamu akan kembali ke lobi.\n\n"
};

// bantuan tentang sistem kematian //
new ajuda_morte[][] =
{
	"\n{00ffff}BANTUAN TENTANG SISTEM KEMATIAN\n\n\n",
	"{ffffff}Ketika nyawa kamu mencapai 0, kamu akan terluka parah dan tidak bisa bergerak, dalam kondisi ini:\n\n",
	"{ffff00}1 {ffffff}Kamu bisa diselamatkan oleh teman yang memiliki\nKit Medis di Inventarisnya atau yang merupakan anggota Tim Medis.\n\n",
	"{ffff00}2 {ffffff}Kamu bisa melakukan Reanimasi Diri sendiri jika memiliki Kit Medis di Inventarismu, dalam hal ini, setiap\ndamage yang diterima akan menyebabkan kematian langsung.\n\n",
	"{ffffff}Informasi Tambahan:\n",
	"{a1a1a1}Ketika reanimasi diri dimulai, tidak dapat dihentikan kecuali kamu menerima damage yang menyebabkan kematianmu.\n",
	"{a1a1a1}Jika kamu terluka parah, musuh bisa menyelesaikan hidupmu dengan menekan tombol H di dekatmu.\n",
	"{a1a1a1}Jika kamu keluar (log out) saat terluka, itu akan menyebabkan kematian langsung.\n",
	"{a1a1a1}Tidak ada batasan waktu untuk memilih apakah akan melakukan reanimasi diri atau diselamatkan oleh temanmu.\n\n"
};




// bantuan tentang peta dan GPS //
new ajuda_mapa_e_gps[][] =
{
	"\n{00ffff}BANTUAN TENTANG PETA DAN GPS\n\n\n",
	"{ffff00}PETA:\n",
	"{ffffff}Jika kamu memiliki {00ff00}Peta{ffffff} di inventarismu, kamu dapat mengaksesnya dengan mudah menggunakan\n",
	"{ffffff}perintah {00ff00}/mapa{ffffff}, di mana kamu bisa menemukan Pos, Bengkel, dan Pasar Gelap.\n\n",
	"{ffff00}GPS:\n",
	"{ffffff}Jika kamu memiliki {00ff00}GPS{ffffff} di inventarismu, kamu bisa {a1a1a1}menyalakan {ffffff}atau {a1a1a1}mematikan {ffffff}dengan mudah menggunakan\n",
	"{ffffff}perintah {00ff00}/gps{ffffff}, di mana kamu akan membuka radar selama interval waktu, sampai\n",
	"{ffffff}baterai GPS-mu habis, jika itu terjadi, kamu hanya bisa menggunakan GPS-mu\n",
	"{ffffff}lagi ketika baterainya minimal {00ffff}30%{ffffff}, baterai akan terisi\n",
	"{ffffff}secara otomatis seiring waktu, kamu akan menerima pesan saat baterainya mencapai {00ffff}100%{ffffff}.\n\n"
};

// bantuan tentang loot dan item yang tersebar //
new ajuda_loot[][] =
{
	"\n{00ffff}BANTUAN TENTANG LOOTS DAN ITEM YANG TERSERAKAN\n\n\n",
	"{ffffff}Saat menjelajahi peta, kamu akan menemukan kotak loot, ada 3 jenis kotak:\n\n",
	"{836FFF}Kelas Rendah {a1a1a1}Di mana kamu akan menemukan item yang lebih sederhana dalam jumlah sedikit.\n",
	"{00ff00}Kelas Menengah {a1a1a1}Di mana kamu akan menemukan item yang sedikit lebih baik dalam jumlah sedang.\n",
	"{ffff00}Kelas Tinggi {a1a1a1}Di mana kamu akan menemukan item terbaik dalam jumlah yang cukup banyak.\n\n",
	"{ffffff}Kamu harus menggunakan {00ffff}F {ffffff}atau {00ffff}ENTER {ffffff}untuk membuka kotak, klik 2 kali pada item, item tersebut akan\n",
	"{ffffff}masuk ke {ffff00}Inventarismu{ffffff}, tekan {00ffff}N {ffffff}untuk membuka inventarismu dan memeriksa item yang kamu ambil.\n",
	"{ffffff}Untuk mengambil {a1a1a1}Item dari tanah{ffffff}, tekan {00ffff}F {ffffff}atau {00ffff}ENTER {ffffff}di dekatnya.\n\n"
};

// INVENTARIO Lobby PLAYER (ketika di looby) //

new mostrando_inv_Lobby[MAX_PLAYERS];
new pagina_Lobby[MAX_PLAYERS];
new info_Lobby[MAX_PLAYERS];
new escolhendo_Lobby[MAX_PLAYERS];






new Inventario_Lobby[MAX_PLAYERS][MAX_LOBBY][invaa];
new Lista_Lobby[MAX_PLAYERS][MAX_LOBBY];



new Mesa[MAX_MESAS][mesa];



new Craft[][objse1] =
{
    // sucata   //madeiras  //metais    //pedras    //plvoras   //ID
	{30, 		0, 			25, 		0, 			6, 		 	2},
	{30, 		25, 		15, 		0, 			10, 		3},
	{20, 		0, 			20, 		0, 			10, 		4},
	{45, 		0, 			20, 		0, 			14, 		13},
	{45, 		0, 			12, 		0, 			10, 	 	16},
	{35, 		0, 			9, 			0, 			0, 		 	6},
	{20, 		10, 		20, 		15, 		10, 	 	7},
	{30, 		10, 		22, 		0, 			10, 	 	8},
	{20, 		0, 			12, 		0, 			8, 		 	9},
	{15, 		30, 		0, 			15, 		10, 	 	11},
	{20, 		0, 			25, 		0, 			0, 		 	19},
	{15, 		15, 		25, 		0, 			0, 		 	22},
	{25, 		35, 		15, 		0, 			0, 		 	23},
	{25, 		20, 		25, 		0, 			0, 		 	24},
	{15, 		15, 		15, 		9, 			0, 		 	25},
	{25, 		0, 			15, 		0, 			0, 		 	71},
	{35, 		35, 		50, 		0, 			10, 	 	87},
	{35, 		10, 		20, 		15, 		20, 		62},
	{35, 		15, 		25, 		20, 		25, 		63},
	{35, 		20, 		30, 		25, 		30, 		64},
	{35, 		15, 		40, 		30, 		28, 		65},
	{35, 		25, 		25, 		15, 		35, 		66},
	{25, 		0, 			15, 		0, 			0, 		 	78},
	{40, 		0, 			20, 		0, 			0, 		 	79},
	{45, 		0, 			25, 		0, 			0, 		 	80},
	{50, 		0, 			40, 		0, 			0, 		 	81},
	{50, 		0, 			55, 		0, 			0, 		 	82},
	{55, 		12, 		40, 		25, 		75, 		54},
	{25, 		15, 		35, 		0, 			30, 		55},
	{30, 		0, 		    30, 		5, 			50, 		131}
};



new RecicladoraPlayer[MAX_PLAYERS][recicles_p];
new Recicladora[MAX_RECICLADORAS][recicles];



new Loot[MAX_LOOT][loooot];



new Carros[MAX_CARROS][fva];



new Oficina[MAX_OFICINAS][ofcs];



new Pos_Oficina[][pos_ofc] =
{
	{12942, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{12943, 0.00000, 0.00000, 0.00000,   0.00000, 0.00000, 0.00000},
	{19872, -0.79221, -0.54211, -1.84286,   0.00000, 0.00000, 90.00000},
	{19899, -7.22389, -1.47524, 0.00045,   0.00000, 0.00000, 0.00000},
	{19899, 2.48081, 3.26781, 0.00040,   0.00000, 0.00000, -90.00000},
	{19815, -1.18010, 3.71762, 1.64852,   0.00000, 0.00000, 0.00000},
	{19900, -2.14810, 3.18340, 0.02930,   0.00000, 0.00000, 0.00000},
	{19900, -1.50520, 3.18500, 0.02930,   0.00000, 0.00000, 0.00000},
	{19900, -0.86630, 3.18910, 0.02930,   0.00000, 0.00000, 0.00000},
	{19900, -0.22180, 3.18980, 0.02930,   0.00000, 0.00000, 0.00000},
	{11745, 4.50995, 3.17333, 1.05745,   0.00000, 0.00000, 40.00000},
	{19900, 4.49364, 3.19453, 0.02930,   0.00000, 0.00000, -24.00000},
	{19921, 7.26254, 3.11008, 0.10761,   0.00000, 0.00000, 0.00000},
	{19921, 7.19097, 3.19770, 0.30229,   0.00000, 0.00000, -25.44000},
	{19921, 5.91726, 3.09528, 0.10761,   0.00000, 0.00000, 21.60000},
	{19921, 2.59262, 3.05045, 1.34464,   0.00000, 0.00000, 0.00000},
	{19921, 3.23550, 3.06076, 1.34464,   0.00000, 0.00000, -25.50000},
	{19921, 2.97726, 3.05771, 2.17912,   0.00000, 0.00000, 23.16000},
	{19921, -6.92504, -1.21250, 1.37097,   0.00000, 0.00000, 90.00000},
	{19921, -7.09765, -0.91753, 2.15935,   0.00000, 0.00000, 59.87999},
	{19921, -6.90357, -2.23717, 1.72844,   0.00000, 0.00000, 90.00000},
	{19903, -7.48365, 0.84827, 0.02287,   0.00000, 0.00000, 0.00000},
	{19900, -7.35926, 1.95430, 0.02930,   0.00000, 0.00000, 0.00000},
	{19900, -7.22692, 2.85012, 0.02930,   0.00000, 0.00000, 23.76000},
	{19921, -7.11580, 2.34871, 1.01146,   0.00000, 0.00000, 76.01998},
	{1025, -4.68160, -3.62025, 0.47935,   0.00000, 0.00000, 90.00000},
	{1073, -7.40191, -3.36602, 0.47930,   0.00000, 0.00000, 45.18000},
	{1074, -3.26948, -3.58605, 0.47930,   0.00000, 0.00000, 90.00000},
	{1079, 2.60920, -3.62600, 0.47930,   0.00000, 0.00000, 90.00000},
	{1080, 1.93470, -3.48250, 0.47930,   0.00000, 0.00000, 124.32000},
	{1082, 7.45370, -3.37480, 0.47930,   0.00000, 0.00000, 141.84000},
	{11745, -1.89377, 3.18538, 1.05745,   0.00000, 0.00000, 107.43999},
	{19621, -1.00193, 3.22605, 1.00583,   0.00000, 0.00000, 50.76000},
	{19621, -0.05567, 3.38911, 1.00583,   0.00000, 0.00000, -13.14001},
	{19621, 1.75997, 3.25469, 1.70984,   0.00000, 0.00000, -53.76000},
	{19621, -7.40669, 1.97237, 1.00235,   0.00000, 0.00000, 0.00000}
};



new Tunings[][tung] =
{
	{"Neon Verde", 18649, 0, 25, 0, 5},               // Neon Green
	{"Neon Marelo", 18650, 0, 25, 0, 5},              // Neon Yellow
	{"Neon Azul", 18648, 0, 0, 25, 5},                // Neon Blue
	{"Neon Vermelho", 18647, 0, 25, 0, 5},            // Neon Red
	{"Neon Branco", 18652, 0, 25, 0, 5},              // Neon White
	{"Objeto Nitro", 1010, 0, 15, 0, 3},              // Nitro Object
	{"Luz Branca", 19280, 0, 10, 0, 5},               // White Light
	{"Giroflex", 18646, 5, 10, 0, 5},                 // Rotating Light (Giroflex)
	{"Extintor", 2690, 0, 15, 0, 10},                 // Fire Extinguisher
	{"Botijao de Gaz", 918, 0, 20, 0, 5},             // Gas Cylinder
	{"Taxi Amarelo", 19308, 0, 20, 0, 5},             // Yellow Taxi
	{"Taxi Preto", 19309, 0, 20, 0, 5},               // Black Taxi
	{"Taxi Branco", 19310, 0, 20, 0, 5},              // White Taxi
	{"Caixa de Som Medio", 2229, 0, 20, 0, 10},       // Medium Sound Box
	{"Caixa de Som Grave", 2232, 0, 25, 0, 10},       // Bass Sound Box
	{"Motor", 19917, 0, 15, 0, 5},                   // Engine
	{"Luzes Policiais", 19419, 0, 10, 0, 10},         // Police Lights
	{"Aerofolio", 1000, 0, 15, 0, 0},                 // Spoiler
	{"Efeito Fogo Pequeno", 18693, 20, 20, 20, 20},    // Small Fire Effect
	{"Efeito Fogo Grande", 18693, 20, 20, 20, 20},    // Large Fire Effect
	{"Efeito Fumaca", 18704, 20, 20, 20, 20},         // Smoke Effect
	{"Efeito Nitro Verde", 18729, 20, 20, 20, 20}     // Green Nitro Effect
};






// dando gmx //
new GMX;



// string gigante para usar //
new String_Gigante[20000];

// teclas usadas no server //
new teclas_server[][] =
{
	"\n\n{ffffff}Tombol {00ffff}N {ffffff}digunakan untuk: {a1a1a1}Membuka Inventaris di mode DAYZ.\n\n",
	"{ffffff}Tombol {00ffff}H {ffffff}digunakan untuk: {a1a1a1}Masuk ke Interior, Menyimpan pemain\nterluka, membuka Pintu, interaksi dengan beberapa menu.\n\n",
	"{ffffff}Tombol {00ffff}Y {ffffff}digunakan untuk: {a1a1a1}Interaksi di menu basis, Api Unggun, Daur Ulang\nKotak Barang, di kendaraan menggantikan perintah /motor, berjalan membuka Hud senjata.\n\n",
	"{ffffff}Tombol {00ffff}F {ffffff}digunakan untuk: {a1a1a1}Mengambil barang dari tanah, memecahkan batu,\nmemecahkan Pohon, Membatalkan beberapa Tindakan, Keluar dari mode Kamera Keamanan.\n\n"
};


// sistemas e informacoes //
new info_server[][] =
{
	"\n{ffffff}Ini adalah server bertema bertahan hidup, lebih dikenal dengan DayZ, dan memiliki berbagai sistem\n",
	"menarik dan dinamis, beberapa sudah dikenal di mode permainan lain, beberapa di antaranya adalah:\n\n",
	"{a1a1a1}",
	"Sistem basis dengan Pemetaan, Pintu, Kotak Barang, Sistem Zombie, Kamera Keamanan, Kerajinan Barang,\n",
	"Kerajinan senjata dengan fragmen, Pasar Hitam, Inventaris di TextDraw, Api Unggun, Sistem Bagasi Mobil, C-4 dan detonator,\n",
	"Pelindung, Helm, Masker Gas, Area dengan Gas Beracun, Senjata dan Amunisi, Ganti Ban Kendaraan,\n",
	"Ganti Baterai Kendaraan, Perbaiki Kendaraan, Alat Perbaiki, Analgesik dan Kit Medis,\n",
	"Menyelamatkan pemain yang terluka, Mengumpulkan Air dan Bensin untuk penggunaan, JetPack dan masih banyak lagi.\n\n",
	"{ffffff}",
	"Kami memiliki sistem VOIP yang berfungsi dengan baik di Android dan PC, di Android gunakan Samp Launcher\n",
	"dan di PC gunakan perintah /voippc untuk mendapatkan link unduhan file, instalasi mudah dan cepat.\n\n",
	"Setelah login, Anda memiliki dua pilihan permainan, mode Cerita yang merupakan Dunia Terbuka di mana sebagian besar\n",
	"sistem berada, dan mode PVP, di mana dua tim yang sudah ditentukan saling berhadapan di peta terbatas.\n\n",
    "{ff0000}PERHATIAN: {a1a1a1}",
	"Seperti server lainnya, server kami juga memiliki beberapa aturan, di mode Cerita dilarang melakukan tindakan seperti Ant Game,\n",
	"DM atau penipuan, ketika bernegosiasi atau tukar barang, disarankan untuk merekam layar atau mengambil screenshot yang jelas, kami akan\n",
	"memberikan hukuman pada pelaku troll dan berusaha semaksimal mungkin untuk membalikkan situasi tersebut.\n\n",
	"{00ffff}Game Mode dibuat oleh Scripter - @anders0n.andre\n\n",
	"{00ff00}Selamat Bermain!!!\n"
};



new ComandosAdmin2[][cmdsadm] =
{
	{"/interior", 1}, {"/mundo", 1}, {"/donobase", 3}, {"/irbase", 3}, {"/destruirbase", 3}, {"/trazerbase", 3}, {"/nomebase", 3}, {"/iractor", 5},{"/copiaractor", 5},{"/criaractor", 5},{"/destruiractor", 5},{"/actor", 5},{"/skinactor", 5},{"/nomeactor", 5},{"/animactor", 5},{"/trazeractor", 5},
	{"/irmercadonegro", 5},{"/criarmercadonegro", 5},{"/destruirmercadonegro", 5},{"/entradamercadonegro", 5},{"/saidamercadonegro", 5}, {"/interiormercadonegro", 5}, {"/mascara", 6}, {"/colete", 6}, {"/capacete", 6}, {"/trazerbau", 6}, {"/trazerrecicladora", 6}, {"/trazermesa", 6}
};

// ini untuk mementukan level admin
new ComandosAdmin[][cmdsadm] =
{
    {"/aa", 1}, {"/a", 1}, {"/atendimentos", 1}, {"/av", 1}, {"/kikar", 1}, {"/ir", 1}, {"/trazer", 1}, {"/rg", 1}, {"/atender", 1}, {"/tv", 1}, {"/trabalho", 1}, {"/teleportes", 1}, {"/listaadmins", 1}, {"/tempoligado", 1},
    {"/punir", 2}, {"/puniroff", 2}, {"/trabalho2", 2}, {"/setarmundo", 2}, {"/setarinterior", 2}, {"/desbanir", 2},  {"/clima", 2},
    {"/banir", 3}, {"/agendarban", 3}, {"/trazerveiculo", 3}, {"/irveiculo", 3},  {"/logs", 3}, {"/destruirportao", 3}, {"/destruircaixa", 3}, {"/destruirmesa", 3}, {"/destruirbau", 3}, {"/destruirrecicladora", 3},
    {"/setarcolete", 4}, {"/setarcapacete", 4}, {"/setarmascara", 4}, {"/setarvida", 4}, {"/setarfome", 4}, {"/setarsede", 4}, {"/setarsono", 4}, {"/setarfrio", 4},
	{"/ajudabases", 5}, {"/ajudamercadonegro", 5}, {"/ajudaactors", 5}, {"/irpos", 5},  {"/verinventario", 5}, {"/verinventarioid", 5},
	{"/carros", 6}, {"/destruircarros", 6}, {"/removeradmin", 6}, {"/daradmin", 6}, {"/setaradmin", 6},  {"/temporespawn", 6}, {"/distancialoot", 6},  {"/destruirobjetosbugados", 6}, {"/gmx2", 6}, {"/gmx", 6}, {"/respawnserver", 6},
  	{"/criarpedra", 7}, {"/editarpedra", 7}, {"/destruirpedra", 7}, {"/criarzombie", 7}, {"/destruirzombie", 7}, {"/idzombie", 7}, {"/criararvore", 7}, {"/editararvore", 7}, {"/destruirarvore", 7}, {"/criaroficina", 7}, {"/destruiroficina", 7}, {"/moveroficina", 7}, {"/createcar", 7}, {"/destroycar", 7}, {"/copycar", 7}, {"/carmoder", 7}, {"/gotocar", 7},
	{"/criarloot", 7}, {"/destruirloot", 7},  {"/editarloot", 7}, {"/irposto", 7}, {"/trazerposto", 7}, {"/destruirposto", 7}, {"/criarposto", 7}, {"/nomeposto", 7}, {"/abastecerposto", 7}, {"/vpncadastros", 7},
	{"/listitems", 8}, {"/criarveiculo", 8}, {"/destruirveiculo", 8}, {"/setarcash", 8},  {"/darcash", 8}, {"/setarlevel", 8}, {"/setarxp", 8}, {"/setarskin", 8}, {"/airdrop", 8}, {"/setarlevelbase", 8}, {"/setarxpbase", 8}, {"/anims", 8}, {"/stopanims", 8}, {"/mudarsenha", 8}, {"/cadastros", 8}, {"/conta", 8}
};



new ComandosPlayers[][cmdspla] =
{
    {"/duvida", "Kirim pesan berisi pertanyaan atau kebingungan kepada Admin yang sedang online."},
    {"/reportar", "Laporkan seorang pemain kepada Admin yang sedang online dengan alasan tertentu."},
    {"/atendimento", "Meminta bantuan/tiket pelayanan kepada admin."},
    {"/encerrar", "Mengakhiri sesi pelayanan yang sedang berlangsung."},
    {"/bases", "Melihat daftar semua basis yang ada di server."},
    {"/par", "Mengirim pesan pribadi kepada pemain lain."},
    {"/ajuda", "Mendapatkan bantuan tentang server dan daftar perintah."},
    {"/vercombates", "Melihat 50 kill terakhir dari Mode Cerita."},
    {"/chatkill", "Melihat 50 kill terakhir dari Mode Cerita."},
    {"/discord", "Melihat link undangan Discord server."},
    {"/creditos", "Melihat informasi mengenai pembuat Game Mode."},
    {"/configuracoes", "Mengaktifkan atau menonaktifkan beberapa fitur."},
    {"/ajudaveiculos", "Membuka menu bantuan tentang perintah kendaraan."},
    {"/criarbase", "Membuat basis milik sendiri, pilih lokasi dengan baik agar tidak merugikan."},
    {"/base", "Membuka menu basis milikmu, jika kamu berada dekat dengan basis tersebut."},
    {"/membros", "Melihat daftar anggota basis yang sedang online."},
    {"/radio", "Membuka radio komunikasi, jika kamu memilikinya di inventaris."},
    {"/cb", "Berbicara di chat basis, jika kamu merupakan anggota dari basis tersebut."},
    {"/portoes", "Melihat gerbang milikmu dari basis."},
    {"/portao", "Mengatur sandi, posisi, dan pengaturan lainnya dari gerbang basis."},
    {"/abrirportao", "Membuka gerbang jika itu milikmu, atau menggunakan sandi yang sesuai."},
    {"/aceitarpedido", "Menerima permintaan dari pemain untuk bergabung ke basis kamu."},
    {"/salvar", "Menyelamatkan pemain yang sedang terluka di tanah, atau tekan H di dekatnya."},
    {"/lobby", "Kembali ke Lobby untuk mengganti mode permainan."},
    {"/jetpack", "Menggunakan jetpack jika kamu memilikinya di inventaris."},
    {"/cameras", "Melihat atau mengatur kamera yang telah kamu pasang."},
    {"/menu", "Digunakan di bengkel untuk membuka menu pilihan."},
    {"/dropar", "Digunakan untuk menjatuhkan kayu, logam, batu, atau bubuk mesiu."},
    {"/pagar", "Digunakan untuk membayar uang kepada seseorang di dekatmu."},
    {"/reparar", "Digunakan oleh profesi Mekanik, menggantikan Kotak Alat."}
};



new MercadoNegro[MAX_MERCADO_NEGRO][mn];

new mostrando_mn[MAX_PLAYERS];

new itens_mercado[][] =
{
	{2,1,500},
	{3,1,1500},
	{4,1,1000},
	{7,1,50},
	{8,1,750},
	{13,1,3500},
	{16,1,2500},
	{22,1,450},
	{26,1,950},
	{37,1,3000},
	{40,1,5000},
	{44,1,4500},
	{62,50,5500},
	{63,25,4500},
	{64,50,5250},
	{65,80,7500},
	{66,30,6000},
	{54,1,10000},
	{55,1,2500}
};

new lista_montar[][] =
{
	{37, 78, 8},
	{38, 78, 6},
	{39, 78, 12},
	{40, 79, 8},
	{41, 79, 12},
	{42, 79, 14},
	{43, 80, 8},
	{44, 80, 10},
	{47, 80, 16},
	{45, 81, 10},
	{46, 81, 14}
};



new Actor[MAX_BOOTS][actors];



// listas dos dialogs //
new LISTA[MAX_PLAYERS][MAX_VEHICLES];

// velocimetro //
new mostrando_velocimetro[MAX_PLAYERS];
new mostrando_velocimetro2[MAX_PLAYERS];



new NomeVeiculos[][] =
{
	"Landstalker","Bravura","Buffalo","Linerunner","Pereniel","Sentinel","Dumper","Firetruck","Trashmaster","Limosine","Manana","Infernus","Voodoo","Pony","Mule","Cheetah","Ambulancia","Leviathan","Moonbeam","Esperanto","Taxi","Washington","Bobcat","Mr Whoopee","BF Injection","Hunter","Premier","Enforcer","Securicar","Banshee","Predator","Bus","Rhino","Barracks","Hotknife","Trailer","Previon","Coach","Cabbie","Stallion","Rumpo","Bandit","Romero","Packer","Monster","Admiral","Squalo","Seasparrow",
	"Pizzaboy","Tram","Trailer","Turismo","Speeder","Reefer","Tropic","Flatbed","Yankee","Caddy","Solair","Berkley's Van","Skimmer","PCJ-600","Faggio","Freeway","Baron","Raider","Glendale","Oceanic","Sanchez","Sparrow","Patriot","Quad","Coastguard","Dinghy","Hermes","Sabre","Rustler","ZR-350","Walton","Regina","Comet","BMX","Burrito","Camper","Marquis","Baggage","Dozer","Maverick","News Chopper","Rancher","FBI Rancher","Virgo","Greenwood","Jetmax","Hotring","Sandking","Blista Compact",
	"Maverick Policial","Boxville","Benson","Mesa","Goblin","Hotring Racer A","Hotring Racer B","Bloodring Banger","Rancher","Super GT","Elegant","Journey","Bike","Mountain Bike","Beagle","Cropdust","Stunt","Tanker","RoadTrain","Nebula","Majestic","Buccaneer","Shamal","Hydra","FCR-900","NRG-500","HPV1000","Cement Truck","Tow Truck","Fortune","Cadrona","FBI Truck","Willard","Forklift","Tractor","Combine","Feltzer","Remington","Slamvan","Blade","Freight","Streak","Vortex","Vincent","Bullet",
	"Clover","Sadler","Firetruck","Hustler","Intruder","Primo","Cargobob","Tampa","Sunrise","Merit","Utility","Nevada","Yosemite","Windsor","Monster A","Monster B","Uranus","Jester","Sultan","Stratum","Elegy","Raindance","Tiger","Flash","Tahoma","Savanna","Bandito","Freight","Trailer","Kart","Mower","Duneride","Sweeper","Broadway","Tornado","AT-400","DFT-30","Huntley","Stafford","BF-400","Newsvan","Tug","Trailer A","Emperor","Wayfarer","Euros","Hotdog","Club","Trailer B","Trailer C",
	"Andromada","Dodo","Cam","Launch","Viatura (LSPD)","Viatura (SFPD)","Viatura (LVPD)","Police Ranger","Picador","S.W.A.T. Van","Alpha","Phoenix","Glendale","Sadler","Luggage Trailer A","Luggage Trailer B","Stair Trailer","Boxville","Farm Plow","Utility Trailer"
};

// SISTEMA TANQUE VEICULO //
new diminuir_gasolina[MAX_VEHICLES];
new diminuir_bateria[MAX_VEHICLES];




new tanque[][tan] =
{
	{400, -1.0666, -2.0648, -0.0336},
	{401, 1.2509, -0.9118, 0.0414},
	{402, 1.1253, -1.8887, 0.1878},
	{403, -1.4199, 0.0898, -0.7618},
	{404, -1.0461, -2.3626, 0.0146},
	{405, -0.8312, -2.2115, -0.0906},
	{400, -1.0666, -2.0648, -0.0336},//
	{407, -1.1796, -3.6276, -0.4843},
	{408, -1.4633, 1.3570, -0.5983},
	{409, -1.0532, -2.8210, 0.1223},
	{410, -0.9792, -1.6566, 0.2390},
	{411, 1.0672, -2.1113, 0.0913},
	{412, -1.1491, -1.8713, -0.0102},
	{413, -0.2491, 0.3609, -0.7968},
	{414, -0.6520, -0.7071, -0.7031},
	{415, -1.0815, -2.0646, 0.0282},
	{416, -1.1579, -2.7675, -0.2045},
	{400, -1.0666, -2.0648, -0.0336},//
	{418, -1.2572, -1.7116, 0.0298},
	{419, -1.1015, -1.9992, 0.0517},
	{420, -1.0183, -2.1997, 0.0691},
	{421, -1.0410, -2.4097, -0.1637},
	{422, -0.9403, -0.4167, -0.2050},
	{423, -1.1336, -1.8601, -0.2726},
	{424, 0.1898, 1.0891, 0.3423},
	{400, -1.0666, -2.0648, -0.0336},//
	{426, -1.0142, -2.1821, 0.0388},
	{427, -1.2523, -3.1149, -0.1290},
	{428, -0.8634, -2.4614, -0.7267},
	{429, -1.0508, -1.6040, 0.2450},
	{400, -1.0666, -2.0648, -0.0336},//
	{431, -1.3081, -5.4853, -0.1576},
	{400, -1.0666, -2.0648, -0.0336},//
	{433, -1.5012, 0.1959, -0.6631},
	{434, -0.7333, -1.6282, 0.2637},
	{400, -1.0666, -2.0648, -0.0336},//
	{436, -1.0347, -1.8145, 0.1429},
	{400, -1.0666, -2.0648, -0.0336},//
	{438, -1.0458, -1.9675, -0.0256},
	{439, -0.7864, -1.5185, -0.0810},
	{440, -0.8978, -0.4473, -0.4651},
	{400, -1.0666, -2.0648, -0.0336},//
	{442, -1.1785, -2.2049, 0.0713},
	{443, -1.3020, 1.2752, -0.9048},
	{444, -1.6624, -1.9008, 0.8128},
	{445, -1.0709, -1.9364, 0.1504},
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{448, -0.2738, 0.0172, 0.1811},
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{451, 1.0966, -1.2476, -0.0004},
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{455, -1.5096, 0.0061, -0.7591},
	{456, 0.7062, -0.0559, -0.6104},
	{457, -0.7963, -0.9864, 0.2263},
	{458, -1.1016, -2.0540, -0.1103},
	{459, -0.9772, -2.3172, 0.2109},
	{400, -1.0666, -2.0648, -0.0336},//
	{461, -0.0551, -0.0729, 0.8215},
	{462, -0.3122, -0.2567, 0.1840},
	{463, -0.2036, 0.3175, 0.4841},
	{464, 0.0341, 0.3076, 0.5485},
	{400, -1.0666, -2.0648, -0.0336},//
	{466, -1.0895, -1.7821, 0.1259},
	{467, -0.9122, -2.3166, 0.0571},
	{468, -0.0687, 0.1206, 0.6902},
	{400, -1.0666, -2.0648, -0.0336},//
	{470, -1.1805, -2.3756, 0.2402},
	{471, -0.2473, -0.1927, 0.6284},
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{474, -1.1542, -1.8663, 0.1502},
	{475, -1.0878, -1.5939, 0.1539},
	{400, -1.0666, -2.0648, -0.0336},//
	{477, -1.0756, -1.5491, 0.1572},
	{478, -1.2159, -0.6237, -0.2496},
	{479, -1.0932, -1.9649, 0.1038},
	{480, -1.1292, -0.8383, 0.1636},
	{400, -1.0666, -2.0648, -0.0336},//
	{482, 1.0334, -2.2679, 0.0034},
	{483, 0.8240, -2.5338, -0.0485},
	{400, -1.0666, -2.0648, -0.0336},//
	{485, -0.8898, 0.7165, 0.0487},
	{486, -0.7272, -3.0480, 0.5854},
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{489, 1.2239, -0.7419, 0.0126},
	{490, 1.4342, -1.0804, 0.0367},
	{491, -1.0491, -2.1652, 0.0345},
	{492, -1.0836, -2.0819, 0.1661},
	{400, -1.0666, -2.0648, -0.0336},//
	{494, -1.0118, -2.1855, 0.1328},
	{495, 1.1669, -1.9102, -0.1244},
	{496, 1.0943, -1.8146, 0.1439},
	{400, -1.0666, -2.0648, -0.0336},//
	{498, -1.2135, -0.0139, 0.0936},
	{499, -1.1789, -1.0767, -0.3417},
	{500, -0.9356, -1.6893, -0.0889},
	{400, -1.0666, -2.0648, -0.0336},//
	{502, -0.9598, -1.8802, 0.1389},
	{503, -0.9941, -2.0333, 0.0356},
	{504, -1.1373, -1.8103, 0.1433},
	{505, 1.2252, -0.7359, 0.0259},
	{506, 0.9764, -1.1418, -0.1125},
	{507, -1.1085, -2.2839, 0.0907},
	{508, -1.3552, -3.0560, -0.6771},
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{514, -1.4881, -0.8220, -0.2419},
	{515, -1.1655, 0.4932, -1.3502},
	{516, -1.1134, -2.4544, 0.0222},
	{517, -1.1252, -1.9533, 0.0729},
	{518, 1.0976, -2.1861, -0.0938},
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{521, -0.1157, 0.1197, 0.5564},
	{522, -0.1419, 0.1843, 0.5410},
	{523, -0.1204, 0.2539, 0.5295},
	{524, 1.3088, 0.4204, -1.0252},
	{525, -1.3094, -0.5072, -0.0926},
	{526, -0.9416, -1.9282, 0.0416},
	{527, -1.1369, -1.7401, 0.1497},
	{528, -0.9437, -2.0821, 0.0636},
	{529, -1.1534, -2.1981, 0.2154},
	{530, -0.7753, -0.7589, 0.0505},
	{531, -0.4879, 0.7874, 0.0627},
	{532, 0.4923, -2.1983, -0.8892},
	{533, 0.8519, -1.9278, 0.1219},
	{534, -1.0129, -0.8377, -0.2085},
	{535, -1.1235, -1.7630, 0.1290},
	{536, -0.9931, -1.7176, 0.0918},
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{539, -0.9428, -1.4909, 0.5522},
	{540, -1.2347, -2.5355, -0.0161},
	{541, -0.8298, -1.5162, 0.2428},
	{542, -0.9897, -1.9030, 0.2966},
	{543, -1.0045, -0.9786, -0.0276},
	{544, -1.1610, 2.0504, 0.3283},
	{545, -0.8038, -1.4394, 0.1997},
	{546, 1.2460, -1.9512, 0.1583},
	{547, -1.0852, -2.0194, 0.1293},
	{400, -1.0666, -2.0648, -0.0336},//
	{549, -0.9162, -1.1492, 0.1792},
	{550, -1.1092, -2.4151, -0.0170},
	{551, -1.0278, -2.6865, 0.0449},
	{552, -1.0377, -0.9234, 0.4505},
	{400, -1.0666, -2.0648, -0.0336},//
	{554, 1.2833, -2.3967, 0.1104},
	{555, -0.8504, -1.4696, 0.2180},
	{556, -1.4501, -1.6580, 0.8123},
	{557, -1.5764, -1.7067, 0.8149},
	{558, -0.8439, -1.9259, 0.2428},
	{559, -1.0394, -1.7852, 0.2269},
	{560, 1.0095, -1.8510, 0.1874},
	{561, 1.1346, -2.3446, 0.1430},
	{562, 0.9326, -0.6781, 0.0374},
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{565, 0.9506, -0.8773, 0.0999},
	{566, 1.1746, -2.2720, 0.0731},
	{567, -1.1706, -1.6422, -0.0657},
	{568, -0.3995, -0.5744, 0.3512},
	{569, 0.4064, -0.5565, 0.3391},
	{400, -1.0666, -2.0648, -0.0336},//
	{571, 0.6567, -0.4675, 0.4549},
	{572, -0.4613, -1.0042, 0.1713},
	{573, -1.4058, 0.4573, -0.4484},
	{574, -0.6276, -0.9450, 0.2338},
	{575, -1.0648, -1.7181, 0.1454},
	{576, -1.1147, -1.7607, 0.1803},
	{400, -1.0666, -2.0648, -0.0336},//
	{578, -1.3332, 2.8953, -0.0219},
	{579, 1.1323, -2.2998, 0.1642},
	{580, 1.2473, -1.7707, 0.2760},
	{581, -0.0707, -0.1368, 0.8255},
	{582, -0.8259, 0.0759, -0.3511},
	{583, -0.5888, 0.3242, -0.1713},
	{400, -1.0666, -2.0648, -0.0336},//
	{585, 1.0833, -2.2879, 0.1858},
	{586, -0.0434, -0.0416, 0.8117},
	{587, -1.2358, -1.1857, 0.1200},
	{588, -1.1486, -2.0738, 0.1753},
	{589, 0.9818, -0.8978, 0.1054},
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{596, -1.0129, -2.1326, 0.0551},
	{597, -1.0385, -2.1507, 0.0580},
	{598, -1.0870, -1.9616, 0.1715},
	{599, 1.4331, -0.7620, 0.0379},
	{600, 0.9428, -2.0202, 0.0482},
	{601, -1.3616, -1.6967, 0.9403},
	{602, 0.9866, -1.9461, 0.0787},
	{603, 1.2402, -2.1992, -0.0256},
	{604, -1.0971, -1.7927, 0.1282},
	{605, -0.9431, -0.9272, -0.0707},
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336},//
	{609, -1.2680, -0.0175, 0.0940},
	{400, -1.0666, -2.0648, -0.0336},//
	{400, -1.0666, -2.0648, -0.0336}//
};

// fogueiras //
new fogueira_player[MAX_PLAYERS];
new fogueira_player2[MAX_PLAYERS];
new fogueira_player3[MAX_PLAYERS];



new Fogueira[MAX_FOGUEIRAS][foguei];




new Tipo_Fogueira[][fog] =
{
	// 71 adalah sebuah panci //

	{"Daging Matang", 70, 1, 71, -1, -1, 69, -1, -1},         // Panci + Daging Mentah
	{"Kopi Panas", 73, 1, 71, -1, -1, 72, 68, -1},            // Panci + Bubuk Kopi + Gelas Air
	{"Burger", 75, 1, 71, -1, -1, 69, 74, -1}                 // Panci + Daging Mentah + Roti
};


// sstema de hora certa //
new hora_certa = -1;



// greenzone
new Area[][area] =
{
	{0, -1, 2500, 20000,  167.5638,   1888.3837, "Area 51"},
		// tinggi, lebar
	{0, -1, 20000, 5000, -2384.0000, -1593.7500, "Mont Chiliad"},
	{0, -1, 400, 550, 2608.0000,  -2510.0000, "Area Kapal"},
	{0, -1, 350, 350, -2440.0000,  2377.3638, "Area Latihan"}
};






new mostrando_mascara[MAX_PLAYERS];



new Objetos[][objse] =
{
    { -0.01622, -0.32363, 1.02817, 000.0, 0, 40, 10, 0, TIPO_BAU, 11729, "Brankas Material"},
	{ -0.06950, -0.01580, 1.23565, 180.0, 40, 10, 0, 0, TIPO_MESA, 3383, "Meja Craft"},
	{  0.04568, -0.18416, 0.49113, 000.0, 0, 35, 15, 5, TIPO_RECICLADORA, 1773, "Mesin Daur Ulang"},
	{  0.47871, 0.02266, 0.69448,  000.0, 25, 10, 0, 5, TIPO_CADEIRA, 1724, "Kursi Kulit"},
	{  0.02525, -0.03365, 1.23383, 000.0, 25, 25, 0, 10, TIPO_ABAJU, 2069, "Lampu Meja"},
	{ -0.30880, -0.58575, 0.85403, 000.0, 25, 30, 0, 15, TIPO_JBL, 2229, "Radio JBL"},
	{  0.05093, 2.14815, 0.90516,  000.0, 45, 10, 0, 0, TIPO_CAMA, 1796, "Tempat Tidur"},
	{  0.18905, -0.15196, 0.35631, 90.00, 25, 0, 0, 0, TIPO_OBJETO, 19356, "Dinding Kayu"},
	{  0.18905, -0.15196, 0.35631, 90.00, 10, 0, 0, 0, TIPO_OBJETO, 19429, "Dinding Kecil Kayu"},
	{  0.18905, -0.15196, 0.35631, 90.00, 50, 0, 0, 0, TIPO_OBJETO, 19448, "Dinding Besar Kayu"},
	{  0.18905, -0.15196, -0.29804, 90.0, 25, 0, 0, 0, TIPO_OBJETO, 19402, "Jendela Kayu"},
	{  0.14603, -0.80199, -0.29804, 90.0, 25, 0, 0, 0, TIPO_OBJETO, 19386, "Pintu Masuk Kayu"},
	{  0.02620, -0.06508, 0.53890, 000.0, 75, 15, 0, 10, TIPO_CAIXA, 1271, "Kotak Barang"},
	{  0.07504, 0.24378, -0.51419, 180.0, 0, 60, 20, 25, TIPO_PORTAO, 980, "Gerbang Besar"},
	{  0.12049, -0.73921, -1.12511, 90.0, 0, 45, 10, 10, TIPO_PORTAO, 2930, "Gerbang Kecil"},
	{  0.02027, -0.00195, 0.70215,  90.0, 20, 10, 0, 0, TIPO_OBJETO, 1516, "Meja Kayu"},
	{  0.02027, -0.00195, -0.99847, 00.0, 0, 15, 20, 15, TIPO_OBJETO, 19806, "Lampu Gantung"},
	{ -0.25092, -2.27374, 1.26394, 000.0, 75, 15, 10, 5, TIPO_OBJETO, 3415, "Kamar Kayu"},
	{  5.85926, -0.39237, 2.04690, 000.0, 0, 50, 10, 5, TIPO_OBJETO, 987, "Pagar Besi"},
	{  5.72650, -1.79479, -3.23306,-90.0, 75, 60, 45, 5, TIPO_OBJETO, 3749, "Pintu Masuk Markas"},
	{  1.86852, -3.55714, -1.29276,-90.0, 100, 10, 0, 5, TIPO_OBJETO, 17037, "Atap Kayu"},
	{ -0.76209,  1.00346, 0.74270, -90.0, 0, 55, 5, 0, TIPO_OBJETO, 13011, "Tangga Besi"},
	{  1.89724, -0.48396, 1.73294,  90.0, 20, 100, 45, 0, TIPO_OBJETO, 3279, "Pos Jaga dengan Tangga"}
};



new Obj[MAX_OBJETOS][objs];
new Objetos_Proximos[MAX_PLAYERS][MAX_OBJETOS];



// localizar coisas //
new Localizando[MAX_PLAYERS];
new Localizando_ID[MAX_PLAYERS];



new Portao[MAX_PORTOES][port];
new Lista_Portao[MAX_PLAYERS][MAX_PORTOES];




new Caixa[MAX_CAIXAS][cai];
new Lista_Caixa[MAX_PLAYERS][MAX_SLOTS];







new Base[MAX_BASES][bas];
new Membro[MAX_BASES][MAX_MEMBROS][MAX_PLAYER_NAME];
new SV_GSTREAM:CanalBase[MAX_BASES];

// resultado //
new mostrando_resultado[MAX_PLAYERS];


// joja da partida //

new mostrando_loja[MAX_PLAYERS];
new pagina_loja[MAX_PLAYERS];
new item_loja[MAX_PLAYERS];


new Armas_Loja5[][] = {{22, 250}, {23, 250}, {24, 250}};
new Armas_Loja4[][] = {{25, 1000}, {26, 1000}, {27, 1000}};
new Armas_Loja3[][] = {{28, 1000}, {29, 1000}, {32, 1000}};
new Armas_Loja2[][] = {{30, 1500}, {31, 1500}};
new Armas_Loja1[][] = {{33, 2500}, {34, 2500}};





new Admin[MAX_ADMINS][adms];
new ModoAdmin[MAX_PLAYERS];
new ListaAdmin[MAX_PLAYERS][MAX_ADMINS];



new Float:SpawnTime[][][] =
{
	{{ 210.9008,-28.5235,1.5781,183.5656 },{ 197.1412,-29.0855,1.5781,178.1136 },{ 188.4186,-30.8588,1.5781,181.3096},{ 227.1492,-29.4401,1.4202,181.3096}, {216.3769,-172.4965,1.5781,88.4368}, { 203.1467,-180.6253,1.5781,354.9999 },{ 201.4645,-161.1465,1.5781,87.6848 },{ 175.2943,-174.1865,1.5703,0.0760 }},
    {{ -70.7234,105.8903,3.1172,155.7774 },{ -64.0290,103.2397,3.1172,155.7774 },{ -55.8484,99.0405,3.1172,155.7774 },{ -46.8667,95.8918,3.1172,155.7774 }, {-117.7366,-43.6239,3.1172,339.6198 },{ -107.2824,-50.3756,3.1172,341.1238 },{ -94.2859,-58.1032,3.1172,333.2278 },{ -87.8464,-62.8264,3.1172,338.6798 }},
	{{-1371.8418,1494.6841,11.0391,93.7369},{-1365.9974,1490.8501,11.0391,85.0888},{-1367.5159,1485.5082,11.0391,88.6609},{-1372.7729,1483.2239,11.0391,88.0969},{-1462.9644,1482.9364,8.2578,270.4352},{-1473.0684,1490.0753,8.2578,267.4272},{-1461.7802,1495.8625,8.2578,267.4272},{-1459.7028,1489.2576,8.2501,270.0593}},
	{{ 1877.6718,-1153.1521,23.8961,231.9182},{1882.6720,-1147.6893,24.0366,231.9182},{1876.2063,-1143.9709,23.8984,224.9621},{1871.5646,-1145.6725,23.7326,232.1063},{ 2051.1970,-1258.6428,23.8203,54.0686 },{ 2055.0164,-1251.9214,23.9844,54.0686 },{ 2060.2083,-1244.2765,23.9844,54.0686 },{ 2062.6604,-1255.7858,23.8203,55.5726 }},
	{{ 413.7543,2537.0586,19.1484,177.6322 },{ 414.8791,2532.4800,19.1465,60.1311 },{ 404.5117,2542.5793,16.5463,110.3275 },{414.0704,2532.6038,16.5779,87.9553 },{ 207.4409,2608.6582,17.5309,273.7010 },{ 223.9436,2581.3069,16.6799,192.8602 },{ 216.1730,2592.1641,16.4766,241.7173 },{ 238.8941,2642.9199,16.5110,265.7815 }},
	{{ 1823.9000,2835.8511,10.8359,120.4331 },{ 1823.9000,2835.8511,10.8359,120.4331 },{ 1808.0059,2864.0007,10.8359,193.3777 },{ 1815.0750,2870.8479,10.8359,168.1855 },{ 1734.0178,2735.1970,11.0447,353.5319 },{ 1728.7498,2756.3696,11.1160,2.1799 },{ 1749.7681,2732.1621,11.1240,304.6514 },{ 1762.1593,2732.6008,10.8359,342.4397 }}
};

new Mapa[][maps] =
{
	{"Desa Kecil", 				0, 999, 184.1372,-107.3921, 200, 200},
	{"Ladang Jerami", 			0, 999, -78.1898, 31.0402, 200, 200 },
	{"Kapal", 					0, 999, -1418.1050,1492.0964, 150, 70},
	{"Taman Gleen", 			0, 999, 1952.1676,-1202.2554, 100, 100},
	{"Kuburan Pesawat", 		0, 999, 308.4663,2566.3777, 230, 230},
	{"Kolam Renang", 			0, 999, 1766.0214,2804.3203, 170, 170}
};







new Sala[MAX_SALAS][sals];
new Sala_Ganhou[MAX_SALAS];
new angulo[MAX_SALAS];
new tempo_mudar[MAX_SALAS];
new Salas[MAX_PLAYERS][MAX_SALAS];
new TimePlayer[MAX_PLAYERS] = {-1, ...};
new mostrando_sala[MAX_PLAYERS];
new SalaPlayer[MAX_PLAYERS];
new dono_sala[MAX_PLAYERS];
new Pronto[MAX_PLAYERS];
new SalaSpawn[MAX_SALAS][2][4];
new SalaMortes[MAX_PLAYERS];
new SalaKills[MAX_PLAYERS];
new Players[MAX_PLAYERS][MAX_PLAYERS];



new Posto[MAX_POSTOS][post];

//  sistema de mostrar dano //

new dano_causado[MAX_PLAYERS];
new dano_sofrido[MAX_PLAYERS];
new dano_causado_arma[MAX_PLAYERS];
new dano_sofrido_arma[MAX_PLAYERS];
new dano_causado_player[MAX_PLAYERS];
new dano_sofrido_player[MAX_PLAYERS];
new timer_dano[MAX_PLAYERS];


// jetpack //
new JetPack[MAX_PLAYERS];
new com_jetpack[MAX_PLAYERS];
new mostrando_jetpack[MAX_PLAYERS];


// Lobby //
new mostrando_login[MAX_PLAYERS];

new AFK[MAX_PLAYERS];

// MODO DE JOGO //
new Modo[MAX_PLAYERS];
new Morto[MAX_PLAYERS];
new Reanimando[MAX_PLAYERS];


// posicoes aleatorias // 
// posisi acak //
new Float:pos_aleatoria[][] =
{
    {2786.5522,-1967.1100,13.5469,67.0245},    // Spawn 1
    {1124.0820,-2037.7665,69.8848,264.8547},   // Spawn 2
    {1873.8047,-2069.1260,15.2120,0.8767},     // Spawn 3
    {1320.3336,-1679.4146,13.5469,94.0761},    // Spawn 4
    {1410.9310,-1490.1917,20.4421,225.8446},   // Spawn 5
    {2422.5808,-1354.0850,24.1444,89.3058},    // Spawn 6
    {2459.9521,-1101.8289,43.6093,341.6251},   // Spawn 7
    {2785.0681,-1358.0946,26.0861,260.5572},   // Spawn 8
    {2488.4207,9.8739,28.4453,185.2051},       // Spawn 9
    {2249.0454,109.9824,28.4453,175.1417},     // Spawn 10
    {1308.9768,380.3336,19.5625,157.4696},     // Spawn 11  
    {249.4914,-92.7751,2.8051,95.3715},        // Spawn 12
    {795.1531,-510.7296,17.2605,178.2098},     // Spawn 13
    {738.9113,-1431.7059,13.7056,175.6849},    // Spawn 14
    {405.6243,-1727.2799,8.7988,3.6268},       // Spawn 15
    {610.2562,-1084.8052,58.8267,38.8483},     // Spawn 16
    {1034.0981,-809.7983,101.8516,22.5261},    // Spawn 17
    {1406.4635,-1301.1570,13.5511,270.6024},   // Spawn 18
    {1488.4340,-1722.0129,8.1958,163.3422},    // Spawn 19
    {2127.2642,-1686.2653,15.0859,45.1596}     // Spawn 20
};


//  timer de cada player //
new timer_player[MAX_PLAYERS] = {-1, ...};




new Barra[MAX_PLAYERS][carg];


// cameras de seguranca //
new cameras[MAX_PLAYERS][100];
new olhando_camera[MAX_PLAYERS];



new Camera[MAX_CAMERAS][cam];

// craft //

new Madeiras[MAX_PLAYERS];
new Metais[MAX_PLAYERS];
new Pedras[MAX_PLAYERS];
new Polvoras[MAX_PLAYERS];

new craft_id[MAX_PLAYERS];
new craft_tipo[MAX_PLAYERS];
new craft_player[MAX_PLAYERS];
new craft_arma[MAX_PLAYERS];



new Pedra[MAX_ARVORES][arv];
new Arvore[MAX_ARVORES][arv];



// VER ARMAS //
new mostrando_arma[MAX_PLAYERS];
new armas[MAX_PLAYERS][13][3];

new mostrando_id[MAX_PLAYERS];
new maximo_armas[MAX_PLAYERS];



new lista_armas[][arm] =
{
	{ 0,  0,   0, 3.0, 0, "Tangan Kosong"},
	{ 19, 1, 331, 4.0, 0, "Brass Knuckle"},
	{ 20, 2, 333, 5.0, 1, "Tongkat Golf"},
	{ 21, 3, 334, 5.0, 1, "Pentungan"},
	{ 22, 4, 335, 5.0, 1, "Pisau"},
	{ 23, 5, 336, 5.0, 1, "Tongkat Baseball"},
	{ 24, 6, 337, 7.0, 1, "Sekop"},
	{ 25, 7, 338, 6.0, 1, "Tongkat Biliar"},
	{ 26, 8, 339, 11.0, 1, "Katana"},
	{ 27, 9, 341, 3.0, 1, "Gergaji Mesin"},
	{ 28, 10, 321, 5.0, 10, "Dildo Ungu"},
	{ 29, 11, 322, 5.0, 10, "Dildo"},
	{ 30, 12, 323, 5.0, 10, "Vibrator"},
	{ 31, 13, 324, 5.0, 10, "Vibrator Perak"},
	{ 32, 14, 325, 5.0, 10, "Bunga"},
	{ 33, 15, 326, 5.0, 10, "Tongkat Jalan"},
	{ 34, 16, 342, 50.0, 8, "Granat"},
	{ 35, 17, 343, 8.0, 8, "Gas Air Mata"},
	{ 36, 18, 344, 7.5, 8, "Molotov"},
	{ 0, 19, 0, 0.0, 0, "Tidak Dikenal"},
	{ 0, 20, 0, 0.0, 0, "Tidak Dikenal"},
	{ 0, 21, 0, 0.0, 0, "Tidak Dikenal"},
	{ 37, 22, 346, 10.0, 2, "9mm"},
	{ 38, 23, 347, 9.0, 2, "9mm Berperedam"},
	{ 39, 24, 348, 28.0, 2, "Desert Eagle"},
	{ 40, 25, 349, 32.0, 3, "Senapan"},
	{ 41, 26, 350, 28.0, 3, "Senapan Gergaji"},
	{ 42, 27, 351, 18.0, 3, "Senapan Tempur"},
	{ 43, 28, 352, 11.0, 4, "Micro SMG / Uzi"},
	{ 44, 29, 353, 10.0, 4, "MP5"},
	{ 45, 30, 355, 23.0, 5, "AK-47"},
	{ 46, 31, 356, 21.0, 5, "M16"},
	{ 47, 32, 372, 9.0, 4, "Tec-9"},
	{ 48, 33, 357, 40.0, 6, "Senapan Country"},
	{ 49, 34, 358, 80.0, 6, "M24"},
	{ 50, 35, 359, 100.0, 7, "RPG"},
	{ 51, 36, 360, 150.0, 7, "Peluncur Roket Terkunci"},
	{ 52, 37, 361, 7.5, 7, "Molotov"},
	{ 53, 38, 362, 30.0, 7, "Minigun"},
	{ 54, 39, 363, 100.0, 8, "Satchel Charge"},
	{ 55, 40, 364, 0.0, 12, "Detonator"},
	{ 56, 41, 365, 5.0, 9, "Kaleng Semprot"},
	{ 57, 42, 366, 5.0, 9, "Pemadam Kebakaran"},
	{ 58, 43, 367, 0.0, 9, "Kamera"},
	{ 59, 44, 368, 0.0, 11, "Kacamata Malam"},
	{ 60, 45, 369, 0.0, 11, "Kacamata Termal"},
	{ 61, 46, 371, 0.0, 11, "Parasut"}
};




new Zombie[MAX_ZOMBIES][zom];


new Arma_Player[MAX_PLAYERS];




new E_Colete[MAX_SKINS][equip];
new E_Capacete[MAX_SKINS][equip];
new E_Mascara[MAX_SKINS][equip];


//  Informacoes do player //
new Logado[MAX_PLAYERS];






new Android[MAX_PLAYERS];
new pInfo[MAX_PLAYERS][playerinfo];
new Vida[MAX_PLAYERS];
new players_perto[MAX_PLAYERS];

new mostrando_info[MAX_PLAYERS];
new mostrando_info2[MAX_PLAYERS];
new mostrando_Lobby[MAX_PLAYERS];


/////////////// SISTEMA DE INVENTARIO //////////////

new Capacete[MAX_PLAYERS][2];
new Colete[MAX_PLAYERS][2];
new Mascara[MAX_PLAYERS];





new Inventario[MAX_PLAYERS][MAX_SLOTS][inv];
new Lista_Inventario[MAX_PLAYERS][MAX_SLOTS];

// textdraws do inv //





new invaberto[MAX_PLAYERS];
new mostrando_opcoes[MAX_PLAYERS];
new pagina_recolher[MAX_PLAYERS];
new pagina_itens[MAX_PLAYERS];
new recolhendo[MAX_PLAYERS];
new escolhendo[MAX_PLAYERS];
new combinando[MAX_PLAYERS];
new guardando[MAX_PLAYERS];
new separando[MAX_PLAYERS];





new Veiculo[MAX_VEICULOS][vei];
new Info_Veiculo[MAX_VEHICLES];

// porta malas //

new mostrando_portamalas[MAX_PLAYERS];
new pagina_portamalas[MAX_PLAYERS];
new ListaPortaMalas[MAX_PLAYERS][MAX_PORTA_MALAS];
new selecionando_portamalas[MAX_PLAYERS];
new PortaMalas[MAX_VEICULOS][MAX_PORTA_MALAS][inv];




////////////  FIM DO INVENTARIO //////////////////


// CONFIGURACOES //
new dialog_player[MAX_PLAYERS];
new timer_dialog_player[MAX_PLAYERS] = {-1, ...};





new Item[MAX_ITENS][itens_recolher];
new Lista_Player[MAX_PLAYERS][MAX_ITENS];



// todas as cores //
new Cores[] =
{
	0x000000FF, 0xF5F5F5FF, 0x2A77A1FF, 0x840410FF, 0x263739FF, 0x86446EFF, 0xD78E10FF, 0x4C75B7FF, 0xBDBEC6FF, 0x5E7072FF,
	0x46597AFF, 0x656A79FF, 0x5D7E8DFF, 0x58595AFF, 0xD6DAD6FF, 0x9CA1A3FF, 0x335F3FFF, 0x730E1AFF, 0x7B0A2AFF, 0x9F9D94FF,
	0x3B4E78FF, 0x732E3EFF, 0x691E3BFF, 0x96918CFF, 0x515459FF, 0x3F3E45FF, 0xA5A9A7FF, 0x635C5AFF, 0x3D4A68FF, 0x979592FF,
	0x421F21FF, 0x5F272BFF, 0x8494ABFF, 0x767B7CFF, 0x646464FF, 0x5A5752FF, 0x252527FF, 0x2D3A35FF, 0x93A396FF, 0x6D7A88FF,
	0x221918FF, 0x6F675FFF, 0x7C1C2AFF, 0x5F0A15FF, 0x193826FF, 0x5D1B20FF, 0x9D9872FF, 0x7A7560FF, 0x989586FF, 0xADB0B0FF,
	0x848988FF, 0x304F45FF, 0x4D6268FF, 0x162248FF, 0x272F4BFF, 0x7D6256FF, 0x9EA4ABFF, 0x9C8D71FF, 0x6D1822FF, 0x4E6881FF,
	0x9C9C98FF, 0x917347FF, 0x661C26FF, 0x949D9FFF, 0xA4A7A5FF, 0x8E8C46FF, 0x341A1EFF, 0x6A7A8CFF, 0xAAAD8EFF, 0xAB988FFF,
	0x851F2EFF, 0x6F8297FF, 0x585853FF, 0x9AA790FF, 0x601A23FF, 0x20202CFF, 0xA4A096FF, 0xAA9D84FF, 0x78222BFF, 0x0E316DFF,
	0x722A3FFF, 0x7B715EFF, 0x741D28FF, 0x1E2E32FF, 0x4D322FFF, 0x7C1B44FF, 0x2E5B20FF, 0x395A83FF, 0x6D2837FF, 0xA7A28FFF,
	0xAFB1B1FF, 0x364155FF, 0x6D6C6EFF, 0x0F6A89FF, 0x204B6BFF, 0x2B3E57FF, 0x9B9F9DFF, 0x6C8495FF, 0x4D8495FF, 0xAE9B7FFF,
	0x406C8FFF, 0x1F253BFF, 0xAB9276FF, 0x134573FF, 0x96816CFF, 0x64686AFF, 0x105082FF, 0xA19983FF, 0x385694FF, 0x525661FF,
	0x7F6956FF, 0x8C929AFF, 0x596E87FF, 0x473532FF, 0x44624FFF, 0x730A27FF, 0x223457FF, 0x640D1BFF, 0xA3ADC6FF, 0x695853FF,
	0x9B8B80FF, 0x620B1CFF, 0x5B5D5EFF, 0x624428FF, 0x731827FF, 0x1B376DFF, 0xEC6AAEFF, 0x000000FF,
	0x177517FF, 0x210606FF, 0x125478FF, 0x452A0DFF, 0x571E1EFF, 0x010701FF, 0x25225AFF, 0x2C89AAFF, 0x8A4DBDFF, 0x35963AFF,
	0xB7B7B7FF, 0x464C8DFF, 0x84888CFF, 0x817867FF, 0x817A26FF, 0x6A506FFF, 0x583E6FFF, 0x8CB972FF, 0x824F78FF, 0x6D276AFF,
	0x1E1D13FF, 0x1E1306FF, 0x1F2518FF, 0x2C4531FF, 0x1E4C99FF, 0x2E5F43FF, 0x1E9948FF, 0x1E9999FF, 0x999976FF, 0x7C8499FF,
	0x992E1EFF, 0x2C1E08FF, 0x142407FF, 0x993E4DFF, 0x1E4C99FF, 0x198181FF, 0x1A292AFF, 0x16616FFF, 0x1B6687FF, 0x6C3F99FF,
	0x481A0EFF, 0x7A7399FF, 0x746D99FF, 0x53387EFF, 0x222407FF, 0x3E190CFF, 0x46210EFF, 0x991E1EFF, 0x8D4C8DFF, 0x805B80FF,
	0x7B3E7EFF, 0x3C1737FF, 0x733517FF, 0x781818FF, 0x83341AFF, 0x8E2F1CFF, 0x7E3E53FF, 0x7C6D7CFF, 0x020C02FF, 0x072407FF,
	0x163012FF, 0x16301BFF, 0x642B4FFF, 0x368452FF, 0x999590FF, 0x818D96FF, 0x99991EFF, 0x7F994CFF, 0x839292FF, 0x788222FF,
	0x2B3C99FF, 0x3A3A0BFF, 0x8A794EFF, 0x0E1F49FF, 0x15371CFF, 0x15273AFF, 0x375775FF, 0x060820FF, 0x071326FF, 0x20394BFF,
	0x2C5089FF, 0x15426CFF, 0x103250FF, 0x241663FF, 0x692015FF, 0x8C8D94FF, 0x516013FF, 0x090F02FF, 0x8C573AFF, 0x52888EFF,
	0x995C52FF, 0x99581EFF, 0x993A63FF, 0x998F4EFF, 0x99311EFF, 0x0D1842FF, 0x521E1EFF, 0x42420DFF, 0x4C991EFF, 0x082A1DFF,
	0x96821DFF, 0x197F19FF, 0x3B141FFF, 0x745217FF, 0x893F8DFF, 0x7E1A6CFF, 0x0B370BFF, 0x27450DFF, 0x071F24FF, 0x784573FF,
	0x8A653AFF, 0x732617FF, 0x319490FF, 0x56941DFF, 0x59163DFF, 0x1B8A2FFF, 0x38160BFF, 0x041804FF, 0x355D8EFF, 0x2E3F5BFF,
	0x561A28FF, 0x4E0E27FF, 0x706C67FF, 0x3B3E42FF, 0x2E2D33FF, 0x7B7E7DFF, 0x4A4442FF, 0x28344EFF
};



// sistema de mapa //
new id_mapa[MAX_PLAYERS];
new mostrando_mapa[MAX_PLAYERS];


// sistema de gps //
new GZ_PRETA;
new player_gps[MAX_PLAYERS];
new gps_player[MAX_PLAYERS];
new mostrando_gps[MAX_PLAYERS];



//// informacoes de zombies ////
new ID_Zombie[MAX_PLAYERS];



new Info_Zombies[][infos_z] =
{
	{0, 0, 0, 0, 0, 0, 0 },
	{162, 50, 4, 1, 0, 0, 1 },
	{162, 75, 6, 1, 0, 1, 1 },
	{162, 110, 7, 1, 1, 0, 1 },
	{162, 150, 9, 1, 1, 1, 1 },
	{200, 50, 3, 1, 0, 0, 1 },
	{200, 75, 2, 1, 0, 1, 1 },
	{200, 110, 8, 1, 1, 0, 1 },
	{200, 150, 9, 1, 1, 1, 1 }
};


new anims_String[1000];
new anims_lastlib[MAX_PLAYERS][50];



// servidor //

new nome_player[MAX_PLAYERS][MAX_PLAYER_NAME];
new pagina_bases[MAX_PLAYERS];
new base_player[MAX_PLAYERS];
new Lista_Admins[MAX_PLAYERS][MAX_ADMINS];
new Lista_Bases[MAX_PLAYERS][MAX_BASES];
new MORREU_POS[MAX_PLAYERS];
new tempo_salvar_conta[MAX_PLAYERS];
new montando_carro[MAX_PLAYERS];
new distancia_loot;
new carregamento_lento;
new tempo_respawn;
new respawn_auto;
new selecionando[MAX_PLAYERS];
new camera_sniper[MAX_PLAYERS];
new fumando[MAX_PLAYERS];
new string_prox[300];
new tempo_ligado;
new SkinTime[] = {230, 134};
new SkinInicial[] = {MASCULINO, FEMININO};
new senhaplayer[MAX_PLAYERS][20];
new falando[MAX_PLAYERS];
new DynamicText3D:player3d[MAX_PLAYERS];


new Apagar[1000][apags];
new Float:RandomFloat1[] ={ 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
new Float:RandomFloat2[] ={ 0.1, 0.2, 0.3, 0.4, -0.1, -0.2, -0.3, -0.4 };


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                                        /////////////////////////////////
///////////////////////////////////////////                 SERVIDOR               /////////////////////////////////
///////////////////////////////////////////                                        /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


