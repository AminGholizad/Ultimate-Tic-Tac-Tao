#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <algorithm>
// time limiting
#include <sys/time.h>
inline double get_time_ms(){
  struct timeval t;
  gettimeofday(&t, NULL);
  return (t.tv_sec + (t.tv_usec / 1000000.0)) * 1000.0;
}
auto TIME_LIMIT = 1000;//milliseconds
//end time limiting
#ifndef INF
#define INF 2147483646
#endif
enum Mark {Draw=-1,Empty=0,Xmark=1,Omark=2};
std::map<Mark, char> symbols = {{Xmark,'x'},{Omark,'o'},{Empty,'-'},{Draw,'#'}};
using Move=std::pair<int,int>;
using a9x9=std::array<std::array<Mark,9>,9>;
using a3x3=std::array<std::array<Mark,3>,3>;
class Board {
private:
  a9x9 board{Empty};
  a3x3 largeboard {Empty};
  Mark winner {Empty};
  Move prev {-1,-1};
  std::vector<Move> valid_moves{};
  Mark me {Omark};
  Mark op {Xmark};
  inline void bring_to_first(Move const& move) {
    auto it = std::find(valid_moves.begin(),valid_moves.end(),move);
    std::rotate(valid_moves.begin(),it,it+1);
  }
  inline bool is_largeboard_full()const& {
    for (auto i=0;i<3;i++){
      for (auto j=0;j<3;j++){
        if (largeboard[i][j]==Empty){
          return false;
        }
      }
    }
    return true;
  }
  inline auto sub_win_count()const& {
    int MEsum = 0;
    int OPsum = 0;
    for (auto i=0;i<3;i++){
      for (auto j=0;j<3;j++){
        if (largeboard[i][j]==me){
          MEsum+=1;
        }
        else if (largeboard[i][j]==op){
          OPsum+=1;
        }
      }
    }
    return std::tuple(MEsum,OPsum);
  }
  inline auto compute_winner(Mark const& mark)const& {
    for (auto i=0;i<3;i++) {
      if (largeboard[i][0]==mark && largeboard[i][1]==mark && largeboard[i][2]==mark){
        return mark;
      }
      if (largeboard[0][i]==mark && largeboard[1][i]==mark && largeboard[2][i]==mark){
        return mark;
      }
    }
    if (largeboard[0][0]==mark && largeboard[1][1]==mark && largeboard[2][2]==mark){
      return mark;
    }
    if (largeboard[0][2]==mark && largeboard[1][1]==mark && largeboard[2][0]==mark){
      return mark;
    }
    if (is_largeboard_full()){
      auto [MEsum,OPsum] = sub_win_count();
      return (MEsum>OPsum)? me : op;
    }
    return Empty;
  }
  inline bool is_sub_winner(int const& x,int const& y,Mark const& mark)const& {
    for(auto i=0;i<3;i++) {
      if(board[i+x][y]==mark && board[i+x][1+y]==mark && board[i+x][2+y]==mark){
        return true;
      }
      if(board[x][i+y]==mark && board[1+x][i+y]==mark && board[2+x][i+y]==mark){
        return true;
      }
    }
    if(board[x][y]==mark && board[1+x][1+y]==mark && board[2+x][2+y]==mark){
      return true;
    }
    if(board[x][2+y]==mark && board[1+x][1+y]==mark && board[2+x][y]==mark){
      return true;
    }
    return false;
  }
  inline bool is_sub_full(int const& x, int const& y)const& {
    for(auto i=x;i<x+3;i++) {
      for(auto j=y;j<y+3;j++){
        if(board[i][j]==Empty){
          return false;
        }
      }
    }
    return true;
  }
  inline void fill_sub(int const& x, int const& y,Mark const& mark) {
    for(auto i=x;i<x+3;i++) {
      for(auto j=y;j<y+3;j++){
        board[i][j]=mark;
      }
    }
  }
  inline void update_prev(int const& x,int const& y) {
    prev.first = x;
    prev.second = y;
  }
  inline void update_largeboard(Mark const& mark) {
    int lx = prev.first / 3;
    int ly = prev.second / 3;
    int sx = lx * 3;
    int sy = ly * 3;
    if (is_sub_winner(sx,sy,mark)){
      largeboard[lx][ly]=mark;
      fill_sub(sx,sy,mark);
      winner = compute_winner(mark);
    }else if (is_sub_full(sx,sy)){
      largeboard[lx][ly]=Draw;
      fill_sub(sx,sy,Draw);
      winner = compute_winner(mark);
    }
  }
  inline void get_valid_moves() {
    valid_moves.clear();
    int lx = prev.first % 3;
    int ly = prev.second % 3;
    int sx = lx * 3;
    int sy = ly * 3;
    if (largeboard[lx][ly]==Empty){
      for(auto i=0;i<3;i++) {
        for(auto j=0;j<3;j++){
          if(board[i+sx][j+sy]==Empty){
            valid_moves.emplace_back(i+sx,j+sy);
          }
        }
      }
    }
    else{
      for(auto i=0;i<9;i++) {
        for(auto j=0;j<9;j++){
          if(board[i][j]==Empty){
            valid_moves.emplace_back(i,j);
          }
        }
      }
    }
  }
  inline auto game_over()const& {
    return std::make_tuple(valid_moves.empty(),winner==me,winner==op);
  }
  inline auto sim_move(int const& x,int const& y,Mark const& mark)const& {
    auto cp=*this;
    cp.board[x][y]=mark;
    cp.update_prev(x,y);
    cp.update_largeboard(mark);
    cp.get_valid_moves();
    return cp;
  }
  inline auto negamax(double end_time, int depth, int alpha=-INF, int beta=INF, int color=1)const& {
    auto [l,m,o] = game_over();
    if (m || o){
      return std::make_pair(color*(m-o)*100*(depth+1),Move());
    }
    if (depth==0 || l || get_time_ms()>=end_time){
      auto [MEsum,OPsum] = sub_win_count();
      return std::make_pair(color*(MEsum - 2*OPsum)*(depth+1),Move());
    }
    int maxEval = -INF;
    auto best_move = valid_moves[0];
    for (auto m : valid_moves){
      auto [x,y] = m;
      auto mark = (color==1) ? me : op;
      auto obj = sim_move(x,y,mark);
      auto [val,move] = obj.negamax(end_time,depth-1,-beta,-alpha,-color);
      if (-val>maxEval){
        maxEval = -val;
        best_move = m;
      }
      alpha = (alpha<maxEval)?maxEval:alpha;
      if (beta<=alpha){
        break;
      }
    }
    return std::make_pair(maxEval,best_move);
  }
  inline auto choose_move() {
    auto best_move = valid_moves[0];
    auto end_time = get_time_ms() + TIME_LIMIT;
    int depth=1;
    while (get_time_ms()<end_time){
      auto [val,move] = negamax(end_time,depth);
      if (get_time_ms()>=end_time){
          std::cerr << "The best move I could find while looking " << depth << " moves ahead\n";
          break;
      }
      // move the best move so far to the first of the vector to consider it first, this may prune more
      bring_to_first(move);
      best_move = move;
      depth++;
    }
    return best_move;
  }
  inline bool is_valid(int x, int y){
      return std::find(valid_moves.begin(),valid_moves.end(),Move(x,y))!=valid_moves.end();
  }
  inline void init_valid_moves(){
    valid_moves.clear();
    for(int i=0;i<9;++i){
      for(int j=0;j<9;++j){
        valid_moves.emplace_back(i,j);
      }
    }
  }
public:
  //constructors
  inline Board() = default;
  inline Board(Board const&) = default;
  inline Board(Board&&) = default;
  inline Board& operator=(Board const&) = default;
  inline Board& operator=(Board&&) = default;

  //debug
  inline void debugLargeboard()const& {
    for (auto& row : largeboard) {
      std::cerr << "|";
      for (auto& elem : row) {
        std::cerr << symbols[elem] << "|";
      }
      std::cerr << '\n';
    }
    std::cerr << '\n';
  }
  inline void debugSubboard(int const& x, int const& y)const& {
    for(auto row : {0,1,2}) {
      std::cerr << "|";
      for(auto col : {0,1,2}){
        std::cerr << symbols[board[row+x][col+y]] << "|";
      }
      std::cerr << '\n';
    }
    std::cerr << '\n';
  }
  inline void debugBoard()const& {
    for (auto& row : board) {
      std::cerr << "|";
      for (auto& elem : row) {
        std::cerr << symbols[elem] << "|";
      }
      std::cerr << '\n';
    }
    std::cerr << '\n';
  }
  inline void debugValidMoves()const& {
    std::cerr<<"Your valid moves are:\n";
    for (auto move : valid_moves){
      std::cerr << move.first << ' ' << move.second << '\n';
    }
    std::cerr << '\n';
  }

  //main methods
  inline auto get_winner()const& {
    return winner;
  }
  inline void op_move() {
    int x,y;
    switch (1){
      case 0:
        do{
          std::cerr<<"Please enter a valid move\n";
      [[fallthrough]];
      case 1:
          std::cin >> x >> y; std::cin.ignore();
          if (x==-1 && y==-1 && me!=Xmark){
            me = Xmark;
            op = Omark;
            valid_moves.clear();
            return;
          }
        }while(!is_valid(x,y));
    }
      
    board[x][y]=op;
    update_prev(x,y);
    update_largeboard(op);
  }
  inline void set_valid_moves() {
    if(valid_moves.empty()){
      init_valid_moves();
    }
    else{
      get_valid_moves();
    }
  }
  inline void move() {
    auto [x,y] = choose_move();
    board[x][y] = me;
    update_prev(x,y);
    update_largeboard(me);
    std::cout << x << ' ' << y << '\n';
  }
};
int main() {
  Board board{};
  board.set_valid_moves();
  std::cerr<<"Enter your move (-1 -1 to start as second player):\n";
  while (true) {
    board.op_move();
    if (board.get_winner()!=Empty){
      break;
    }
    board.set_valid_moves();
    board.move();
    board.debugBoard();
    if (board.get_winner()!=Empty){
      break;
    }
    board.set_valid_moves();
    board.debugValidMoves();
  }
  std::cout<< symbols[board.get_winner()] << " wins!"<<'\n';
  return 0;
}
