#include "front.hpp"

WINDOW * ringue;
WINDOW * enfermaria;
WINDOW * quadroG;

#define T_CHARGE 800000
#define T_POWER   80000
#define T_BLOD   800000  

void time (WINDOW* win, int udelay)
{
  wrefresh(win);
  usleep(udelay); 
}

void printChar(WINDOW* win, int y, int x, int color, int val)
{
    string s_l; 
    s_l += val == -1 ? ' ' : val + 65 + '\0';
    
    const char* l = s_l.c_str();
    wattron(win, COLOR_PAIR(color));
    mvwprintw(win, y, x, l);
    wattroff(win, COLOR_PAIR(color)); 
}

void printChar(WINDOW* win, int y, int x, int color, const char* c)
{
    wattron(win, COLOR_PAIR(color));
    mvwprintw(win, y, x, c);
    wattroff(win, COLOR_PAIR(color)); 
}

void desenhaLeito(int n_leitos)
{
  int width_enf, height_enf;
  int margin_x, margin_y, dist_x, dist_y, n_lin, n_col;
  getmaxyx(enfermaria, height_enf, width_enf);

  float ratio = (float) ((float) height_enf/width_enf);

  n_col = round(sqrt((float) n_leitos/ratio));
  n_lin = ceil(ratio * n_col);

  margin_x = dist_x = width_enf/(n_col + 1);
  margin_y = dist_y = height_enf/(n_lin + 1);
  
  for (int i = 1; i <= n_col; i++)
  {
    for (int j = 1; j <= n_lin; j++)
    {
      if (n_col*(j-1) + i <= n_leitos)
      {
        // subtract i by -1 because the warriors will be at second pos.
        printChar(enfermaria, j*margin_y, i*margin_x-1, 2, "___/");
      }
    }
  }
  wrefresh(enfermaria);
}

void printPacientes(vector<int> & pacientes, int n_leitos, vector<int> y_id, vector<int> x_id)
{

  sort(pacientes.begin(), pacientes.end());

  // breaks here
/*
  for (int l = 0; l < (int) pacientes.size(); l++)
  {
    printChar(enfermaria, y_id[l], x_id[l], 2, pacientes[l]);
  }
  for (int l = n_leitos - pacientes.size() - 1; l < n_leitos; l++)
    printChar(enfermaria, y_id[l], x_id[l], 2, pacientes[l]);
// */
}

void desenhaPacientesDinamico (vector<int> & pacientes, int n_leitos)
{ 
  vector<int> x_id;
  vector<int> y_id;
  
  int width_enf, height_enf;
  int margin_x, margin_y, dist_x, dist_y, n_lin, n_col;
  getmaxyx(enfermaria, height_enf, width_enf);

  float ratio = (float) ((float) height_enf/width_enf);

  n_col = round(sqrt((float) n_leitos/ratio));
  n_lin = ceil(ratio * n_col);

  margin_x = dist_x = width_enf/(n_col + 1);
  margin_y = dist_y = height_enf/(n_lin + 1);
  
  for (int i = 1; i <= n_col; i++)
  {
    for (int j = 1; j <= n_lin; j++)
    {
      if (n_col*(j-1) + i <= n_leitos)
      {
        // subtract i by -1 because the warriors will be at second pos.
        // printChar(enfermaria, j*margin_y, i*margin_x-1, 2, "___/");
        x_id.push_back(i*margin_x);
        y_id.push_back(j*margin_y);
      }
    }
  }
  wrefresh(enfermaria);
  ///////////*************//////////////// crash here
  printPacientes(pacientes, n_leitos, y_id, x_id);
}

void printLuts(WINDOW* win, vector<vector<int> > &luts, vector<int> & y_id, 
                  vector<vector<int> > & x_id, 
                  bool pos, int color, unsigned utime)
{
  int n_pits = y_id.size();
  for (int n = 0; n < n_pits; n++)
  {
    int y = y_id[n];
    int x = x_id[pos][n];
    int val = luts[pos][n];
    if (val > -1 && luts[1- pos][n] > -1)
      printChar(win, y, x, color, val);
  }
  time(win, utime);
}

void printPowersSync(vector<vector<int> > &luts, 
                     vector<vector<int> > &x_id, vector<int> &y_id)
{
  // int n_pits = luts.size();
  // int size_pits = x_id[1][0] - x_id[0][0]; // - 1;
  
  printLuts(ringue, luts, y_id, x_id, 0, 6, T_CHARGE);
  printLuts(ringue, luts, y_id, x_id, 0, 1, 0);

  // POWER INI
  /*
  for (int i = 1; i < size_pits; i++)
  {
    for (int n = 0; n < n_pits; n++)
    {
      int y = y_id[n];
      int x = i + x_id[0][n];

      printChar(ringue, y, x, 6, "-");
    }
    time(ringue, T_POWER);

    for (int n = 0; n < n_pits; n++)
    {
      int y = y_id[n];
      int x = i + x_id[0][n];
      printChar(ringue, y, x, 6, " ");
    }
  }
  */
  // POWER ENDS

  printLuts(ringue, luts, y_id, x_id, 1, 50, T_BLOD);
  printLuts(ringue, luts, y_id, x_id, 1, 1, 0);

  // CANONICAL

  printLuts(ringue, luts, y_id, x_id, 1, 6, T_CHARGE);
  printLuts(ringue, luts, y_id, x_id, 1, 1, 0);

  // POWER INI
  /*
  for (int i = size_pits-1; i >= 0; i--)
  {
    for (int n = 0; n < n_pits; n++)
    {
      int y = y_id[n];
      int x = i + x_id[0][n];
      printChar(ringue, y, x, 6, "-");

    }
    usleep(T_POWER);
    wrefresh(ringue);

    for (int n = 0; n < n_pits; n++)
    {
      int y = y_id[n];
      int x = i + x_id[0][n];
      printChar(ringue, y, x, 6, " ");
    }
  }
  */
  // POWER ENDS

  printLuts(ringue, luts, y_id, x_id, 0, 50, T_BLOD);
  wrefresh(ringue);
  printLuts(ringue, luts, y_id, x_id, 0, 1, 0);
  wrefresh(ringue);
}

// para usar em while
void desenhaLutDinamico (vector<vector<int> > luts)
{ 
  int n_pits = luts.size();
  int margin_x, margin_y, dist_x, dist_y, n_lin, n_col, d_lut;
  int width_ringue, height_ringue;
  getmaxyx(ringue, height_ringue, width_ringue);
  
  float ratio = (float) ((float) height_ringue/width_ringue);

  n_col = round(sqrt((float) (n_pits)/ratio)); // ceil(sqrt(n_pits)); 
  n_lin = ceil(ratio * n_col); // ceil(sqrt(n_pits - n_col)); 

  margin_x = dist_x = width_ringue/(n_col + 1);
  margin_y = dist_y = height_ringue/(n_lin + 1);
  d_lut = (int) (margin_x/3.5);

  vector<vector<int> > x_id(2);
  vector<int> y_id;

  for (int j = 1; j <= n_lin; j++)
  {
    for (int i = 1; i <= n_col; i++)
    {
      int pit = (i + (j-1)*n_col) - 1;

      if (pit <= (n_pits) -1)
      {
        printChar(ringue, j*margin_y, i*margin_x - d_lut, 1, luts[0][pit]);
        printChar(ringue, j*margin_y, i*margin_x + d_lut, 1, luts[1][pit]);

        string id_pit;
        id_pit += pit + 48 + '\0';
        
        printChar(ringue, j*margin_y+1, i*margin_x, 2, (id_pit).c_str());
        
        x_id[0].push_back(i*margin_x - d_lut);
        x_id[1].push_back(i*margin_x + d_lut);
        y_id.push_back(j*margin_y);
      }
    }
  }
  wrefresh(ringue);
  printPowersSync(luts, x_id, y_id);
}

bool drawDinamico(int n_leitos, vector<int> pacientes, vector<vector<int> > lutadores) {
    
    // altura e largura da tela - usado para desenhar as arenas de acordo  
    // com as especificacoes da tela do usuário. 
    int scr_height, scr_width, margin_y = 0, margin_x = 2; 

    // find sizes screen
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    scr_height = w.ws_row;
    scr_width = w.ws_col;

    ui height_enf, width_enf, begin_y_enf, begin_x_enf;
    ui height_lut, width_lut, begin_y_lut, begin_x_lut;
    ui height_qg, width_qg, begin_y_qg, begin_x_qg;

    height_enf = height_lut = ((scr_height-margin_y)/2);
    width_enf =  width_lut = width_qg = ((scr_width - margin_x)/2); 
    height_qg = (height_enf + height_lut + margin_y);

    begin_y_enf = begin_y_qg = 0;
    begin_x_enf = begin_x_lut = 0;
    begin_y_lut = begin_y_enf + height_enf + margin_y;
    begin_x_qg = begin_x_enf + width_enf + margin_x;

    //criação da enfermaria
    enfermaria = newwin(height_enf, width_enf, begin_y_enf, begin_x_enf);
    refresh();                                              
    box(enfermaria, 0, 0);                                  
    mvwprintw(enfermaria, 0, width_enf/2 - 4,"ENFERMARIA");         
    wrefresh(enfermaria);                                   

    //desenhar os leitos inicialmente
    desenhaLeito(n_leitos);

    //criação do ringue
    ringue = newwin(height_lut, width_lut, begin_y_lut, begin_x_lut);
    refresh();
    box(ringue, 0, 0);
    mvwprintw(ringue, 0, width_lut/2 - 3, "RINGUE");
    wrefresh(ringue);  
    
    desenhaLutDinamico(lutadores);
    desenhaPacientesDinamico(pacientes, n_leitos);

    //criação do quadro geral
    quadroG = newwin(height_qg, width_qg, begin_y_qg, begin_x_qg);  
    refresh();
    box(quadroG, 0, 0);
    mvwprintw(quadroG, 0, begin_x_qg/2 - 12, "ESTADO DE CADA LUTADOR");
    wrefresh(quadroG);
    return true;
}

int frontend(int n_leitos, vector<Saiyan*> saiyans){
    initscr();          //inicializa a tela
    cbreak();           //permite c break (apertar control+c para fechar a aplicação)
    noecho();           //faz com que as teclas pressionadas não apareçam no terminal
    // intro();
    start_color();
    if (!has_colors())
    {
      printw("TERMINAL DOES NOT SUPPORT COLORS");
      getch();
      return -1;
    }
    else
    {
      init_pair(1, COLOR_WHITE, COLOR_BLACK);
      init_pair(2, COLOR_YELLOW, A_NORMAL);
      init_pair(3, COLOR_BLUE, A_NORMAL);
      init_pair(4, COLOR_GREEN, A_NORMAL);
      init_pair(5, COLOR_RED, A_NORMAL);
      init_pair(6, COLOR_CYAN, A_NORMAL);
      init_pair(50, A_NORMAL, COLOR_RED);
      init_pair(60, A_NORMAL, COLOR_CYAN);
      init_pair(40, A_NORMAL, COLOR_GREEN);
    }
    drawInicial(n_leitos);     //desenhar as telas principais e inicias

    vector<int>  pacientes;
    vector<vector<int> > lutadores(2);
    
    for(Saiyan* s : saiyans)
    {
      if (s->get_current_state() == State(HEALING))
        pacientes.push_back((int) s->get_id());
    }
    
    for (Pit p : saiyans[0]->get_arena()->get_pits())
    {
      int id1 = p.lutador1 == nullptr ? -1 : p.lutador1->get_id();
      int id2 = p.lutador2 == nullptr ? -1 : p.lutador2->get_id();

      lutadores[0].push_back(id1);
      lutadores[1].push_back(id2);
    }

    bool done = false;
    while (!done){
      done = drawDinamico(n_leitos, pacientes, lutadores);       
    }
    
    // while (getch() != 27){}
    endwin();  //fecha a tela
    return 0;
}




























// ==================================================== ================================================
void drawInicial(int n_leitos) {
    
    // altura e largura da tela - usado para desenhar as arenas de acordo  
    // com as especificacoes da tela do usuário. 
    int scr_height, scr_width, margin_y = 0, margin_x = 2; 

    // find sizes screen
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    scr_height = w.ws_row;
    scr_width = w.ws_col;

    ui height_enf, width_enf, begin_y_enf, begin_x_enf;
    ui height_lut, width_lut, begin_y_lut, begin_x_lut;
    ui height_qg, width_qg, begin_y_qg, begin_x_qg;

    height_enf = height_lut = ((scr_height-margin_y)/2);
    width_enf =  width_lut = width_qg = ((scr_width - margin_x)/2); 
    height_qg = (height_enf + height_lut + margin_y);

    begin_y_enf = begin_y_qg = 0;
    begin_x_enf = begin_x_lut = 0;
    begin_y_lut = begin_y_enf + height_enf + margin_y;
    begin_x_qg = begin_x_enf + width_enf + margin_x;

    //criação da enfermaria
    enfermaria = newwin(height_enf, width_enf, begin_y_enf, begin_x_enf);
    refresh();                                              
    box(enfermaria, 0, 0);                                  
    mvwprintw(enfermaria, 0, width_enf/2 - 4,"ENFERMARIA");         
    wrefresh(enfermaria);                                   

    //desenhar os leitos inicialmente
    desenhaLeito(n_leitos);

    //criação do ringue
    ringue = newwin(height_lut, width_lut, begin_y_lut, begin_x_lut);
    refresh();
    box(ringue, 0, 0);
    mvwprintw(ringue, 0, width_lut/2 - 3, "RINGUE");
    wrefresh(ringue); 

    //criação do quadro geral
    quadroG = newwin(height_qg, width_qg, begin_y_qg, begin_x_qg);  
    refresh();
    box(quadroG, 0, 0);
    mvwprintw(quadroG, 0, begin_x_qg/2 - 12, "ESTADO DE CADA LUTADOR");
    wrefresh(quadroG);
    return;
}

void intro(){
    ui ini_x_saiyadin = 5;
    ui ini_x_name = 10;
    mvprintw(00,ini_x_saiyadin, " .d8888b.                                          .d8888b.           d8b                      d8b d8b                  ");
    mvprintw(01,ini_x_saiyadin, "d88P  Y88b                                        d88P  Y88b          Y8P                      Y8P Y8P                  ");
    mvprintw(02,ini_x_saiyadin, "Y88b.                                             Y88b.                                                                 ");
    mvprintw(03,ini_x_saiyadin, " 'Y888b.   888  888 88888b.   .d88b.  888d888      'Y888b.    8888b.  888 888  888  8888b.    8888 888 88888b.  .d8888b ");
    mvprintw(04,ini_x_saiyadin, "    'Y88b. 888  888 888 '88b d8P  Y8b 888P'           'Y88b.     '88b 888 888  888     '88b   '888 888 888 '88b 88K     ");
    mvprintw(05,ini_x_saiyadin, "      '888 888  888 888  888 88888888 888               '888 .d888888 888 888  888 .d888888    888 888 888  888 'Y8888b.");
    mvprintw(06,ini_x_saiyadin, "Y88b  d88P Y88b 888 888 d88P Y8b.     888         Y88b  d88P 888  888 888 Y88b 888 888  888    888 888 888  888      X88");
    mvprintw(07,ini_x_saiyadin, " 'Y8888P'   'Y88888 88888P'   'Y8888  888          'Y8888P'  'Y888888 888  'Y88888 'Y888888    888 888 888  888  88888P'");
    mvprintw( 8,ini_x_saiyadin, "                    888                                                        888             888                      ");
    mvprintw( 9,ini_x_saiyadin, "                    888                                                   Y8b d88P            d88P                      ");
    mvprintw(10,ini_x_saiyadin, "                    888                                                    'Y88P'           888P'                       ");
    mvprintw(13,ini_x_saiyadin, "   Os Saiyajins são uma raça alienígena super poderosa e formada para guerra, sua maior força vem no seu momento de maior");
    mvprintw(14,ini_x_saiyadin, "fraqueza, quando estão a beira de sua morte, quando ativam um estado chamado Super Saiyajin, em que sua aparência se    ");    
    mvprintw(15,ini_x_saiyadin, "modfica, seu cabelo muda de cor, e sua força vital aumenta assim como seu ataque.                                       ");
    mvprintw(17,ini_x_saiyadin, "   Um grupo de Sayajins decidiram se unir e formar um grupo de luta, onde o objetivo (bem psicopata se parar pra pensar)");
    mvprintw(18,ini_x_saiyadin, "é lutarem entre si, e levarem um ao outro perto o suficiente da morte para ativar o estado Super Saiyajin, sem os riscos");
    mvprintw(19,ini_x_saiyadin, " de morrer, e depois se recuperarem em uma enfermaria, mantendo o aumento de força e energia vital. O objetivo de todos ");
    mvprintw(20,ini_x_saiyadin, "os Sayajins é de atigirem mais de 8000 pontos de energia vital, mas garantindo que sempre que um membro fique machucado ");
    mvprintw(21,ini_x_saiyadin, "haja um leito disponível para ele na Enfermaria.");
    mvprintw(23,ini_x_name, "by Rodrigo de Araujo Sacerdote");
    mvprintw(24,ini_x_name, "   Leonardo Kenji Kobaicy");
    mvprintw(25,ini_x_name, "   Enrique Antonio Ponce Cruz");
    mvprintw(26,ini_x_name, "   Ian Loron de Almeida");
    mvprintw(29,ini_x_name, "PRESS ENTER TO CONTINUE");
    refresh();
    while (getch() != 10){}
    clear();
    return;
}
