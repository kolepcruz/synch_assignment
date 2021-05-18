#include "front.hpp"

WINDOW * ringue;
WINDOW * enfermaria;
WINDOW * quadroG;

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

int frontend(int n_leitos, vector<Saiyan*> saiyans){
  
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
      init_pair(20, A_NORMAL, COLOR_YELLOW);
    }

    vector<int>  pacientes;
    vector<vector<Saiyan*> > fighters(2);
    
    for(Saiyan* s : saiyans)
    {
      if (s->get_current_state() == State(HEALING))
        pacientes.push_back((int) s->get_id());
    }
    
    for (Pit p : saiyans[0]->get_arena()->get_pits())
    {
      fighters[0].push_back(p.lutador1);
      fighters[1].push_back(p.lutador2);
    }
    
    drawScreens(n_leitos, pacientes, fighters, saiyans);

    return 0;
}

void time (WINDOW* win, int udelay)
{
  wrefresh(win);
  usleep(udelay); 
}

void printChar(WINDOW* win, int y, int x, int color, int val)
{
    string s_l;
    // transform int into char
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

void drawInfirmary (vector<int> pacientes, int n_leitos)
{ 
  int width_enf, height_enf;
  int margin_x, margin_y, dist_x, dist_y, n_lin, n_col;
  getmaxyx(enfermaria, height_enf, width_enf);
  sort(pacientes.begin(), pacientes.end());

  float ratio = (float) ((float) height_enf/width_enf);

  n_col = round(sqrt((float) n_leitos/ratio));
  n_lin = ceil(ratio * n_col);

  margin_x = dist_x = width_enf/(n_col + 1);
  margin_y = dist_y = height_enf/(n_lin + 1);
  
  for (int i = 1; i <= n_col; i++)
  {
    for (int j = 1; j <= n_lin; j++)
    {
      int id_leito = (n_col*(j-1) + i) -1;
      if (id_leito < n_leitos)
      {
        // subtract i by -1 because the warriors will be at second pos.
        printChar(enfermaria, j*margin_y, i*margin_x-1, 2, "___/");
        int n_pac = pacientes.size();
        if (id_leito < n_pac)
        {
          printChar(enfermaria, j*margin_y, i*margin_x, 20, pacientes[id_leito]); 
        }
      }
    }
  }
  wrefresh(enfermaria);
}

// para usar em while
void drawFighters (vector<vector<Saiyan*> > fighters)
{ 
  int n_pits = fighters.size();
  int margin_x, margin_y, dist_x, dist_y, n_lin, n_col, d_lut;
  int width_ringue, height_ringue;
  getmaxyx(ringue, height_ringue, width_ringue);
  
  float ratio = (float) ((float) height_ringue/width_ringue);

  n_col = round(sqrt((float) (n_pits)/ratio)); // ceil(sqrt(n_pits)); 
  n_lin = ceil(ratio * n_col); // ceil(sqrt(n_pits - n_col)); 

  margin_x = dist_x = width_ringue/(n_col + 1);
  margin_y = dist_y = height_ringue/(n_lin + 1);
  d_lut = (int) (margin_x/3.5);

  for (int j = 1; j <= n_lin; j++)
  {
    for (int i = 1; i <= n_col; i++)
    {
      int pit = (i + (j-1)*n_col) - 1;

      if (pit <= (n_pits) -1)
      {
        int val_1 = fighters[0][pit] == nullptr ? -1 : fighters[0][pit]->get_id();
        int val_2 = fighters[1][pit] == nullptr ? -1 : fighters[1][pit]->get_id();
        int x_1 = i*margin_x - d_lut;
        int x_2 = i*margin_x + d_lut;
        int y = j*margin_y;

        printChar(ringue, y, x_1, 1, val_1);
        printChar(ringue, y, x_2, 1, val_2);
        
        // print powers and effects
        if (val_1 != -1 && fighters[0][pit]->get_current_state() == State(DEFENDING))
        {
          printChar(ringue, y, x_1, 50, val_1);
          printChar(ringue, y, x_2, 6, val_2);
          printChar(ringue, y, x_2-1, 6, "<");
        }

        else if(val_2 != -1 && fighters[1][pit]->get_current_state() == State(DEFENDING))
        {
          printChar(ringue, y, x_2, 50, val_2);
          printChar(ringue, y, x_1, 6, val_1);
          printChar(ringue, y, x_1+1, 6, ">");
        }

        // print pit  
        string c = string(2*d_lut+1, '-');
        printChar(ringue, y+1, x_1, 2, (const char*) c.c_str());

        // print id pits
        string id_pit;
        id_pit += pit + 48 + '\0';
        printChar(ringue, y+1, i*margin_x, 2, (id_pit).c_str());
      }
    }
  }
  wrefresh(ringue);
}

void drawGenFrame(vector<Saiyan*> saiyans)
{
  int n_lin = saiyans.size();
  int margin_x, dist_y;
  int width_ringue, height_ringue;
  getmaxyx(ringue, height_ringue, width_ringue);  

  // 25 is the (probable) size of the Frame.
  margin_x = (width_ringue - 24+5)/2;
  dist_y = height_ringue/(n_lin + 1);

  string ini_line = "Saiyadins:\n";
  ini_line += "id curr_hp / tot_hp atck c_pit";

  for (int j = 1; j <= n_lin; j++)
  {
    int id = j-1;
    int curr_state = saiyans[id]->get_current_state();
    int color = 1;
    if (curr_state == State(DEFENDING))
      color = 5;
    else if (curr_state == State(HEALING))
      color = 2;
    else if (curr_state == State(FINISHED))
      color = 40;

    char buf[256];
    char pattern[] = "%c %3d /%4d %3d  %2d";
    Saiyan* s = saiyans[id];

    char id_s = s->get_id() + 65 + '\0';
    sprintf(buf, pattern, id_s, s->get_current_hp(),
            s->get_total_hp(), s->get_attack_pwr(),s->current_pit);  
    string line = buf;
    printChar(quadroG, j*dist_y, margin_x, color, line.c_str());
  }
  wrefresh(quadroG);
}

void drawScreens(int n_leitos, vector<int> pacientes, vector<vector<Saiyan*> > fighters,
                vector<Saiyan*> saiyans) {   
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

    drawInfirmary(pacientes, n_leitos);

    //criação do ringue
    ringue = newwin(height_lut, width_lut, begin_y_lut, begin_x_lut);
    refresh();
    box(ringue, 0, 0);
    mvwprintw(ringue, 0, width_lut/2 - 3, "RINGUE");
    wrefresh(ringue);  
    
    drawFighters(fighters);

    //criação do quadro geral
    quadroG = newwin(height_qg, width_qg, begin_y_qg, begin_x_qg);  
    refresh();
    box(quadroG, 0, 0);
    mvwprintw(quadroG, 0, begin_x_qg/2 - 12, "ESTADO DE CADA LUTADOR");
    wrefresh(quadroG);

    drawGenFrame(saiyans);
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
    drawInfirmary({}, n_leitos);

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


/*
void print_in_arena(WINDOW* win, vector<vector<int> > &luts, vector<int> & y_id, 
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
    {
      printChar(win, y, x, color, val);
      // print power
      if (color == 6)
        pos == 0? printChar(win, y, x+1, color, ">"): printChar(win, y, x-1, color, "<");
      else
      {
        printChar(win, y, x+1, color, " "); printChar(win, y, x-1, color, " ");
      }
    }
  }
  // here, contains refresh
  // time(win, utime);
}

void syncPowers(vector<vector<int> > &luts, 
                     vector<vector<int> > &x_id, vector<int> &y_id)
{
  print_in_arena(ringue, luts, y_id, x_id, 0, 6, T_CHARGE);
  print_in_arena(ringue, luts, y_id, x_id, 0, 1, 0);

  print_in_arena(ringue, luts, y_id, x_id, 1, 50, T_BLOD);
  print_in_arena(ringue, luts, y_id, x_id, 1, 1, 0);

  // CANONICAL

  print_in_arena(ringue, luts, y_id, x_id, 1, 6, T_CHARGE);
  print_in_arena(ringue, luts, y_id, x_id, 1, 1, 0);

  print_in_arena(ringue, luts, y_id, x_id, 0, 50, T_BLOD);
  print_in_arena(ringue, luts, y_id, x_id, 0, 1, 0);
}
*/