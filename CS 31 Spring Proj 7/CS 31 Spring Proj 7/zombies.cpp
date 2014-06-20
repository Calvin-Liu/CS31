//
//  main.cpp
//  CS 31 Spring Proj 7
//
//  Created by Calvin on 5/30/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

// zombies.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Island::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
#include <cassert>

#define CHECKTYPE(f, t) { (void)(t)(f); }

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows on the island
const int MAXCOLS = 40;             // max number of columns on the island
const int MAXZOMBIES = 180;         // max number of zombies allowed

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Island;  // This is needed to let the compiler know that Island is a
// type name, since it's mentioned in the Zombie declaration.

class Zombie
{
public:
    // Constructor
    Zombie(Island* ip, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    
private:
    Island* m_island;
    int     m_row;
    int     m_col;
};

class Player
{
public:
    // Constructor
    Player(Island *ip, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    string takeComputerChosenTurn();
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();
    
private:
    Island* m_island;
    int     m_row;
    int     m_col;
    int     m_age;
    bool    m_dead;
};

class Island
{
public:
    // Constructor/destructor
    Island(int nRows, int nCols);
    ~Island();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     zombieCount() const;
    int     nZombiesAt(int r, int c) const;
    void    display(string msg) const;
    
    // Mutators
    bool   addZombie(int r, int c);
    bool   addPlayer(int r, int c);
    bool   destroyZombie(int r, int c);
    bool   moveZombies();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Zombie* m_zombies[MAXZOMBIES];
    int     m_nZombies;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Island* m_island;
};

///////////////////////////////////////////////////////////////////////////
//  Zombie implementation
///////////////////////////////////////////////////////////////////////////

Zombie::Zombie(Island* ip, int r, int c)
{
    if (ip == NULL)
    {
        cout << "***** A zombie must be on some Island!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ip->rows()  ||  c < 1  ||  c > ip->cols())
    {
        cout << "***** Zombie created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_island = ip;
    m_row = r;
    m_col = c;
}

int Zombie::row() const
{
    return m_row;
}

int Zombie::col() const
{
    // TODO: TRIVIAL:  return what column the Zombie is at
    return m_col;
}

void Zombie::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    switch (rand() % 4)
    {
        case UP:
            if(row() > 1)
            {
                m_row--;
            }
            break;
        case DOWN:
            if(row() < m_island->rows())
            {
                m_row++;
            }
            break;
        case LEFT:
            if(col() > 1)
            {
                m_col--;
            }
            break;
        case RIGHT:
            if(col() < m_island->cols())
            {
                m_col++;
            }
            break;
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Island* ip, int r, int c)
{
    if (ip == NULL)
    {
        cout << "***** The player must be on some Island!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ip->rows()  ||  c < 1  ||  c > ip->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_island = ip;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    // TODO:  TRIVIAL:  return the row the player is at
    return m_row;
}

int Player::col() const
{
    // TODO:  TRIVIAL:  return the column the player is at
    return m_col;
}

int Player::age() const
{
    // TODO:  TRIVIAL:  return the player's age
    return m_age;
}

string Player::takeComputerChosenTurn()
{
    // TODO:  replace this implementation:
    // Your replacement implementation should do something intelligent
    // and return a string that describes what happened.  When you've
    // decided what action to take, take it by calling move, shoot, or stand.
    // This function must return one of the following four strings:
    //     "Moved."
    //     "Shot and hit!"
    //     "Shot and missed!"
    //     "Stood."
    
    // Here's one possible strategy:
    //   If moving in some direction would put me in less immediate danger
    //     than standing, then move in that direction.
    //   else shoot in the direction of the nearest zombie I can hit.
    
    // A more aggressive strategy is possible, where you hunt down zombies.
    int right = 0;
    int left = 0;
    int up = 0;
    int down = 0;
    for(int k = col(); k < m_island->cols()+1; k++)
    {
        right++;
        if(m_island->nZombiesAt(row(), k) != 0)
        {
            if(shoot(RIGHT))
                return "Shot and hit!";
            else
                break;
        }
    }
    for(int j = row(); j < m_island->rows()+1; j++)
    {
        down++;
        if(m_island->nZombiesAt(j, col()) != 0)
        {
            if(shoot(DOWN))
                return "Shot and hit!";
            else
                break;
        }
    }
    for(int i = col(); i > 0; i--)
    {
        left++;
        if(m_island->nZombiesAt(row(), i) != 0)
        {
            if(shoot(LEFT))
                return "Shot and hit!";
            else
                break;
        }
    }
    for(int l = row(); l > 0; l--)
    {
        up++;
        if(m_island->nZombiesAt(l, col()) != 0)
        {
            if(shoot(UP))
                return "Shot and hit!";
            else
                break;
        }
    }
    if(right == left && right == up && right == down && down == up && down == left && left == up)
    {
        stand();
        return "Stood";
    }
    if(up > down && up > right && up > left)
    {
        move(UP);
        return "Moved up.";
    }
    else if(down > up && down > right && down > left)
    {
        move(DOWN);
        return "Moved down.";
    }
    else if(right > down && right > up && right > left)
    {
        move(RIGHT);
        return "Moved right.";
    }
    else if(left > down && left > right && left > up)
    {
        move(LEFT);
        return "Moved left.";
    }
    
    return "Shot and missed.";
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;
    switch (dir)
    {
        case UP:
            if(row() > 1)
            {
                m_row--;
            }
            break;
        case DOWN:
            if(row() < m_island->rows())
            {
                m_row++;
            }
            break;
        case LEFT:
            if(col() > 1)
            {
                m_col--;
            }
            break;
        case RIGHT:
            if(col() < m_island->cols())
            {
                m_col++;
            }
            break;
    }
}

bool Player::shoot(int dir)
{
    m_age++;
    
    if (rand() % 3 != 0)  // miss with 2/3 probability
        return false;
    
    // TODO:  destroy the nearest zombie in direction dir
    switch(dir)
    {
        case UP:
            for(int k = row(); k != 0; k--)
            {
                if(m_island->nZombiesAt(k,col()) != 0)    //start here
                {
                    m_island->destroyZombie(k, col());
                    return true;
                }
            }
            break;
        case DOWN:
            for(int h = row(); h != m_island->rows()+1; h++)
            {
                if(m_island->nZombiesAt(h, col()) != 0)
                {
                    m_island->destroyZombie(h, col());
                    return true;
                }
            }
            break;
        case LEFT:
            for(int j = col(); j != 0; j--)
            {
                if(m_island->nZombiesAt(row(), j) != 0)
                {
                    m_island->destroyZombie(row(), j);
                    return true;
                }
            }
            break;
        case RIGHT:
            for(int i = col(); i != m_island->cols()+1; i++)
            {
                if(m_island->nZombiesAt(row(), i) != 0)
                {
                    m_island->destroyZombie(row(), i);
                    return true;
                }
            }
            break;
            
    }
    return false;  // this is wrong -- replace it
}

bool Player::isDead() const
{
    // TODO:  TRIVIAL:  return whether the player is dead
    return m_dead;  // this is wrong -- replace it
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Island implementations
///////////////////////////////////////////////////////////////////////////

Island::Island(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Island created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = NULL;
    m_nZombies = 0;
}

Island::~Island()
{
    for(int k = 0; k < m_nZombies; k++)
    {
        delete m_zombies[k];
    }
}

int Island::rows() const
{
    return m_rows;
}

int Island::cols() const
{
    return m_cols;
}

Player* Island::player() const
{
    return m_player;
}

int Island::zombieCount() const
{
    return m_nZombies;
}

int Island::nZombiesAt(int r, int c) const
{
    int count = 0;
    for(int k = 0; k < m_nZombies; k++)
    {
        if(m_zombies[k]->col() == c && m_zombies[k]->row() == r)
        {
            count++;
        }
    }
    return count;
}

void Island::display(string msg) const
{
    // Position (row,col) in the island coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    // Indicate each zombie's position
    // TODO:  If one zombie is at some grid point, set the char to 'Z'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    for(int i = 0; i < rows()+1; i++)
    {
        for(int j = 0; j < cols()+1; j++)
        {
            if(nZombiesAt(i, j) == 1)
            {
                grid[i-1][j-1] = 'Z';
            }
            else if(nZombiesAt(i, j) >= 2 && nZombiesAt(i, j) <= 8)
            {
                grid[i-1][j-1] = (nZombiesAt(i, j) + '0');
            }
            else if(nZombiesAt(i, j) >= 9)
            {
                grid[i-1][j-1] = '9';
            }
        }
    }
    
    // Indicate player's position
    if (m_player != NULL)
    {
        // Set the char to '@', unless there's also a zombie there,
        // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write message, zombie, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << zombieCount() << " zombies remaining." << endl;
    if (m_player == NULL)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Island::addZombie(int r, int c)
{
    // If MAXZOMBIES have already been added, return false.  Otherwise,
    // dynamically allocate a new zombie at coordinates (r,c).  Save the
    // pointer to the newly allocated zombie and return true.
    // TODO:  Implement this
    if(r < 1 || r > rows() || c < 1 || c > cols())
    {
        return false;
    }
    
    if(zombieCount() == MAXZOMBIES)
        return false;

    m_zombies[m_nZombies] = new Zombie(this, r, c);
    m_nZombies++;
    
    return true;
}

bool Island::addPlayer(int r, int c)
{
    // Don't add a player if one already exists
    if (m_player != NULL)
        return false;
    
    // Dynamically allocate a new Player and add it to the island
    m_player = new Player(this, r, c);
    return true;
}

bool Island::destroyZombie(int r, int c)
{
    // TODO:  destroy one zombie at row r, column c
    if(zombieCount() == 0)
        return false;
    
    for(int k = 0; k < m_nZombies; k++)
    {
        if(m_zombies[k]->row() == r && m_zombies[k]->col() == c) //if you delete zombie 3, hole in array?
        {
            delete m_zombies[k];
            for(int j = k; j < m_nZombies; j++)
            {
                m_zombies[j] = m_zombies[j+1];
            }
            m_nZombies--;
            return true;
        }
    }
    return false;
}

bool Island::moveZombies()
{
    // TODO:  Have the k-th zombie on the island make one move.
    //        If that move results in that zombie being in the same
    //        position as the player, the player dies.
    
    for (int k = 0; k < m_nZombies; k++)
    {
        m_zombies[k]->move();
        if(m_zombies[k]->row() == m_player->row() && m_zombies[k]->col() == m_player->col())
        {
            m_player->setDead();
        }
    }
    
    // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nZombies)
{
    if (nZombies > MAXZOMBIES)
    {
        cout << "***** Trying to create Game with " << nZombies
        << " zombies; only " << MAXZOMBIES << " are allowed!" << endl;
        exit(1);
    }
    
    // Create island
    m_island = new Island(rows, cols);
    
    // Add player
    int rPlayer = 1 + rand() % rows;
    int cPlayer = 1 + rand() % cols;
    m_island->addPlayer(rPlayer, cPlayer);
    
    // Populate with zombies
    while (nZombies > 0)
    {
        int r = 1 + rand() % rows;
        int c = 1 + rand() % cols;
        // Don't put a zombie where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_island->addZombie(r, c);
        nZombies--;
    }
}

Game::~Game()
{
    delete m_island;
}

void Game::play()
{
    Player* p = m_island->player();
    if (p == NULL)
    {
        m_island->display("");
        return;
    }
    string msg = "";
    do
    {
        m_island->display(msg);
        msg = "";
        cout << endl;
        cout << "Move (u/d/l/r/su/sd/sl/sr/c//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)
            p->stand();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'c':  // computer moves player
                    msg = p->takeComputerChosenTurn();
                    break;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->move(decodeDirection(action[0]));
                    break;
                case 's':
                    if (action.size() < 2)  // if no direction, nobody moves
                    {
                        cout << '\a' << endl;  // beep
                        continue;
                    }
                    switch (action[1])
                {
                    default:   // if bad direction, nobody moves
                        cout << '\a' << endl;  // beep
                        continue;
                    case 'u':
                    case 'd':
                    case 'l':
                    case 'r':
                        if (p->shoot(decodeDirection(action[1])))
                            msg = "Hit!";
                        else
                            msg = "Missed!";
                        break;
                }
                    break;
            }
        }
        m_island->moveZombies();
    } while ( ! m_island->player()->isDead()  &&  m_island->zombieCount() > 0);
    m_island->display(msg);
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <cstring>

void clearScreen()
{
    static const char* term = getenv("TERM");
    static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
    if (term == NULL  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
}

#endif

void thisFunctionWillNeverBeCalled()
{
    // If the student deleted or changed the interfaces to the public
    // functions, this won't compile.  (This uses magic beyond the scope
    // of CS 31.)
    
    Zombie(static_cast<Island*>(0), 1, 1);
    CHECKTYPE(&Zombie::row,  int  (Zombie::*)() const);
    CHECKTYPE(&Zombie::col,  int  (Zombie::*)() const);
    CHECKTYPE(&Zombie::move, void (Zombie::*)());
    
    Player(static_cast<Island*>(0), 1, 1);
    CHECKTYPE(&Player::row,     int  (Player::*)() const);
    CHECKTYPE(&Player::col,     int  (Player::*)() const);
    CHECKTYPE(&Player::age,     int  (Player::*)() const);
    CHECKTYPE(&Player::isDead,  bool (Player::*)() const);
    CHECKTYPE(&Player::takeComputerChosenTurn, string (Player::*)());
    CHECKTYPE(&Player::stand,   void (Player::*)());
    CHECKTYPE(&Player::move,    void (Player::*)(int));
    CHECKTYPE(&Player::shoot,   bool (Player::*)(int));
    CHECKTYPE(&Player::setDead, void (Player::*)());
    
    Island(1, 1);
    CHECKTYPE(&Island::rows,          int     (Island::*)() const);
    CHECKTYPE(&Island::cols,          int     (Island::*)() const);
    CHECKTYPE(&Island::player,        Player* (Island::*)() const);
    CHECKTYPE(&Island::zombieCount,   int     (Island::*)() const);
    CHECKTYPE(&Island::nZombiesAt,    int     (Island::*)(int,int) const);
    CHECKTYPE(&Island::display,       void    (Island::*)(string) const);
    CHECKTYPE(&Island::addZombie,     bool    (Island::*)(int,int));
    CHECKTYPE(&Island::addPlayer,     bool    (Island::*)(int,int));
    CHECKTYPE(&Island::destroyZombie, bool    (Island::*)(int,int));
    CHECKTYPE(&Island::moveZombies,   bool    (Island::*)());
    
    Game(1,1,1);
    CHECKTYPE(&Game::play, void (Game::*)());
}

void doBasicTests()
{
    {
        Island zi(10, 20);
        assert(zi.addPlayer(2, 6));
        Player* pp = zi.player();
        assert(pp->row() == 2  &&  pp->col() == 6  && ! pp->isDead());
        pp->move(UP);
        assert(pp->row() == 1  &&  pp->col() == 6  && ! pp->isDead());
        pp->move(UP);
        assert(pp->row() == 1  &&  pp->col() == 6  && ! pp->isDead());
        pp->setDead();
        assert(pp->row() == 1  &&  pp->col() == 6  && pp->isDead());
    }
    {
        Island zi(2, 2);
        assert(zi.addPlayer(1, 1));
        assert(zi.addZombie(2, 2));
        Player* pp = zi.player();
        assert(zi.moveZombies());
        assert( ! pp->isDead());
        for (int k = 0; k < 1000  &&  zi.moveZombies(); k++)
            ;
        assert(pp->isDead());
    }
    {
        Island zi(1, 40);
        assert(zi.addPlayer(1, 1));
        assert(zi.addZombie(1, 40));
        assert(zi.addZombie(1, 40));
        assert(zi.addZombie(1, 39));
        assert(zi.zombieCount() == 3  &&  zi.nZombiesAt(1, 40) == 2);
        Player* pp = zi.player();
        for (int k = 0; k < 1000  &&  zi.zombieCount() != 0; k++) //only killing 1 zombie
            pp->shoot(RIGHT);
        assert(zi.zombieCount() == 0); 
        assert(zi.addZombie(1, 40));
        assert(zi.zombieCount() == 1);
        for (int k = 0; k < 1000  &&  zi.zombieCount() != 0; k++)
            pp->takeComputerChosenTurn();
        assert(zi.zombieCount() == 0); //************
    }
    cout << "Passed all basic tests" << endl;
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Initialize the random number generator.  (You don't need to
    // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));
    
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(1, 40, 3);
    
    // Play the game
    g.play();
    doBasicTests();
}