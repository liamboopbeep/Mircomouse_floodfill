#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include "..\API\API.h"
#include "statemachine.cpp"
#include "statemachine_simplified.cpp"
using namespace std;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
const int rows = 16;
const int cols = 16;

void log(const std::string &text) { std::cerr << text << std::endl; }

typedef struct coor {
  int row;
  int col;
  int value;
} coord;

typedef struct cell_infos {
  // variables for north,east,south,west walls
  bool walls[4];
  bool visited;
  int angle_update;
  bool dead = 0;
} cell_info;

typedef struct wall_mazes {
  cell_info cells[rows][cols];
} wall_maze;

bool isValid(int x, int y) { return (x >= 0 && x < rows && y >= 0 && y < cols); }  // Check ô

wall_maze maze;
const int dx[] = {1, -1, 0, 0};  // di chuyển bằng dx[i]
const int dy[] = {0, 0, -1, 1};  // di chuyển bằng dy[i]
std::queue<coord> myQueue;       // Bắt đầu queue

void init_arr(std::vector<std::vector<int>> &arr, int row, int col) {
  for (int i = 0; i < row; i++) {
    std::vector<int> arr_row;
    for (int j = 0; j < col; j++) {
      arr_row.push_back(-1);  // đẩy giá trị -1 vào tất cả các ô
    }
    arr.push_back(arr_row);
  }
}

void check_and_fill(std::vector<std::vector<int>> &arr, int row, int col, int value) {
  if (row < 0 || col < 0 || row >= arr.size() || col >= arr[0].size() || arr[row][col] != -1) return;  // Nếu ngoài bảng hoặc bằng not filled return không thì +1
  value += 1;
  coord point = {row, col, value};
  myQueue.push(point);
  arr[row][col] = value;
}

void init_flood(std::vector<std::vector<int>> &arr, int row, int col)  // row,col = 7
{
  int count_ = 0;
  coord point = {row, col, count_};
  myQueue.push(point);
  arr[row][col] = 0;

  coord point2 = {row + 1, col, count_};
  myQueue.push(point2);
  arr[row + 1][col] = 0;

  coord point3 = {row, col + 1, count_};
  myQueue.push(point3);
  arr[row][col + 1] = 0;

  coord point4 = {row + 1, col + 1, count_};
  myQueue.push(point4);
  arr[row + 1][col + 1] = 0;
  // tọa độ của 4 ô goals với count = 0
  while (!myQueue.empty()) {
    coord frontCoord = myQueue.front();
    // std::cerr << frontCoord.col << frontCoord.row << frontCoord.value<<std::endl;
    myQueue.pop();
    check_and_fill(arr, frontCoord.row + 1, frontCoord.col, frontCoord.value);
    check_and_fill(arr, frontCoord.row - 1, frontCoord.col, frontCoord.value);
    check_and_fill(arr, frontCoord.row, frontCoord.col + 1, frontCoord.value);
    check_and_fill(arr, frontCoord.row, frontCoord.col - 1, frontCoord.value);
  }
}

void init_flood_start(std::vector<std::vector<int>> &arr, int row_, int col_, int back_ = 0) {
  int count_ = 0;
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      arr[i][j] = -1;
      if (back_ == 2 && maze.cells[i][j].visited == false) {
        arr[i][j] = 255;
        maze.cells[i][j].dead = true;
      }
    }
    // if(back_==2)std::cerr<<"gay"<<std::endl;
  }
  if (back_ != 1) {
    coord point2 = {row_ + 1, col_, count_};
    myQueue.push(point2);

    arr[row_ + 1][col_] = 0;

    coord point3 = {row_, col_ + 1, count_};
    myQueue.push(point3);
    arr[row_][col_ + 1] = 0;

    coord point4 = {row_ + 1, col_ + 1, count_};
    myQueue.push(point4);
    arr[row_ + 1][col_ + 1] = 0;
  }
  coord point = {row_, col_, count_};
  myQueue.push(point);
  arr[row_][col_] = 0;

  while (!myQueue.empty()) {
    coord frontCoord = myQueue.front();
    myQueue.pop();
    for (int i = 0; i < 4; ++i) {
      int newRow = frontCoord.row + dy[i];  // 0 0 -1 1
      int newCol = frontCoord.col + dx[i];  // 1 -1 0 0
      // std::cerr <<dir<< new_cell.walls[dir]<<std::endl ;
      // bool check_=check_wall_angle(maze.cells[cur_stack.row][cur_stack.col],ind_);
      bool check_ = maze.cells[frontCoord.row][frontCoord.col].walls[i];
      if (!check_) check_and_fill(arr, newRow, newCol, frontCoord.value);
    }
    //  std::cerr<<"size:"<<myQueue.size()<<std::endl;
    if (myQueue.size() > 120) {
      log("fulllll");
      break;
    }
  }
}

void update_wall_debug(std::vector<std::vector<int>> &arr) {
  char dir;
  bool clear_ = 0;
  int count_ = 0;
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      std::string value = std::to_string(arr[i][j]);
      for (int k = 0; k < 4; k++) {
        clear_ = maze.cells[i][j].walls[k];

        if (k == 0)
          dir = 'n';
        else if (k == 1)
          dir = 's';
        else if (k == 2)
          dir = 'w';
        else
          dir = 'e';
        if (clear_)
          API::setWall(i, j, dir);
        else
          API::clearWall(i, j, dir);
      }
      if (maze.cells[i][j].visited == true) {
        // log("blue");
        API::setColor(i, j, 'G');  // g-green r-red b-Blue

      } else
        API::clearColor(i, j);  // g-green r-red b-Blue
      if (maze.cells[i][j].dead == true) {
        API::setText(i, j, "Dead");  // g-green r-red b-Blue
        API::setColor(i, j, 'r');    // g-green r-red b-Blue

      }
      // value+="-R:"+std::to_string(i)+"-C:"+std::to_string(j);
      else
        API::setText(i, j, value);
    }
  }
}

bool check_wall_angle(cell_info cell, int &dir) {
  switch (cell.angle_update) {
    case 90:
      break;
    case 270:
      if (dir % 2 == 0)
        dir += 1;
      else
        dir -= 1;
      break;
    case 0:
      if (dir == 0 || dir == 1)
        dir += 2;
      else if (dir == 2)
        dir = 1;
      else
        dir = 0;
      break;
    case 180:
      if (dir == 2 || dir == 3)
        dir -= 2;
      else if (dir == 0)
        dir = 3;
      else
        dir = 2;
      break;
  }
  return cell.walls[dir];
}

cell_info cell_direction_adjust(cell_info cell) {
  cell_info cell_new;
  cell_new = cell;
  for (int i = 0; i < 4; i++) {
    int ind = i;
    switch (cell.angle_update) {
      case 90:
        break;
      case 270:
        if (i % 2 == 0)
          ind += 1;
        else
          ind -= 1;
        break;
      case 0:
        if (i == 0 || i == 1)
          ind += 2;
        else if (i == 2)
          ind = 1;
        else
          ind = 0;
        break;
      case 180:
        if (i == 2 || i == 3)
          ind -= 2;
        else if (i == 0)
          ind = 3;
        else
          ind = 2;
        break;
    }
    cell_new.walls[i] = cell.walls[ind];
  }
  return cell_new;
}

void go_to_cell(int &angle_now, int dir) {
  switch (dir) {
    case -1:
      log("not dir");
      break;
    case UP:
      log("forward");
      API::moveForward();
      break;
    case DOWN:
      log("Down");
      angle_now -= 180;
      API::turnRight();
      API::turnRight();
      API::moveForward();
      break;
    case LEFT:
      log("Left");
      angle_now += 90;
      API::turnLeft();
      API::moveForward();
      break;
    case RIGHT:
      log("right");
      angle_now -= 90;
      API::turnRight();
      API::moveForward();
      break;
    default:
      break;
  }
  angle_now = angle_now % 360;
  // Đảm bảo góc không bị âm
  if (angle_now < 0) {
    angle_now += 360;
  }
}

coord get_min_neighbour(cell_info cell_wall, coord cur, std::vector<std::vector<int>> &arr, bool change_ = 0) {
  int min_neightbor = 255;
  coord next_step;
  next_step.value = -1;
  int ind;
  for (int dir = 0; dir < 4; ++dir) {
    int newRow = cur.row + dy[dir];  // 0 0 -1 1
    int newCol = cur.col + dx[dir];  // 1 -1 0 0
    ind = dir;
    bool check_ = cell_wall.walls[dir];
    if (change_) check_ = check_wall_angle(cell_wall, ind);
    if (isValid(newRow, newCol) && !check_) {
      if (arr[newRow][newCol] <= min_neightbor) {
        min_neightbor = arr[newRow][newCol];
        next_step.row = newRow;
        next_step.col = newCol;
        next_step.value = ind;
      }
    }
  }
  return next_step;
}

void flood(std::stack<coord> &stack_flood, std::vector<std::vector<int>> &arr) {
  coord cur_stack;
  coord next_step;
  while (!stack_flood.empty()) {
    cur_stack = stack_flood.top();
    stack_flood.pop();
    int min_neightbor = 255;
    bool check_;
    next_step = get_min_neighbour(maze.cells[cur_stack.row][cur_stack.col], cur_stack, arr);
    min_neightbor = arr[next_step.row][next_step.col];
    if (arr[cur_stack.row][cur_stack.col] - 1 != min_neightbor) {
      for (int i = 0; i < 4; i++) {
        coord cur_add;
        cur_add.row = cur_stack.row + dy[i];  // 0 0 -1 1
        cur_add.col = cur_stack.col + dx[i];  // 1 -1 0 0
        check_ = maze.cells[cur_stack.row][cur_stack.col].walls[i];
        if (isValid(cur_add.row, cur_add.col) && arr[cur_add.row][cur_add.col] != 0 && !check_) {
          stack_flood.push(cur_add);
        }
      }
      if (arr[cur_stack.row][cur_stack.col] != 0) arr[cur_stack.row][cur_stack.col] = min_neightbor + 1;
      update_wall_debug(arr);
      // log("added");
    }
    int stack_size = stack_flood.size();
    if (stack_size >= 35) {
      log("full stack");
      for (int i = 0; i < stack_size; i++) {
        stack_flood.pop();
      }
      return;
    }
  }
}
cell_info update_walls(int angle_now, int row, int col) {
  cell_info new_cell;
  new_cell.angle_update = angle_now;
  new_cell.walls[UP] = API::wallFront();
  new_cell.walls[DOWN] = 0;
  new_cell.walls[LEFT] = API::wallLeft();
  new_cell.walls[RIGHT] = API::wallRight();
  new_cell.dead = 0;
  new_cell.visited = 1;
  maze.cells[row][col] = cell_direction_adjust(new_cell);
  if (new_cell.walls[UP] == 1 && new_cell.walls[LEFT] == 1 && new_cell.walls[RIGHT] == 1 && row != 0 && col != 0) {
    log("dead");
    maze.cells[row][col].dead = 1;
  }
  for (int i = 0; i < 4; i++) {
    int newRow = row + dy[i];
    int newCol = col + dx[i];
    if (isValid(newRow, newCol)) {
      if (i == UP)
        maze.cells[newRow][newCol].walls[DOWN] = maze.cells[row][col].walls[UP];
      else if (i == LEFT)
        maze.cells[newRow][newCol].walls[RIGHT] = maze.cells[row][col].walls[LEFT];
      else if (i == RIGHT)
        maze.cells[newRow][newCol].walls[LEFT] = maze.cells[row][col].walls[RIGHT];
    }
  }
  return new_cell;
}
coord floodfill(coord start, coord dest, std::vector<std::vector<int>> &arr, int &angle_now) {
  std::queue<coord> path_queue;
  path_queue.push(start);
  coord cur = start;
  cell_info new_cell;
  // cell_info new_cell;
  std::stack<coord> stack_flood;
  stack_flood.push(start);
  int path_distance_value_find = 0;
  int save_row, save_col;
  coord next_step;
  while (1) {
    if (!path_queue.empty())  // dua ra quyet dinh va go
    {
      cur = path_queue.front();
      new_cell = update_walls(angle_now, cur.row, cur.col);
      if (arr[cur.row][cur.col] == arr[dest.row][dest.col]) break;
      flood(stack_flood, arr);
      path_queue.pop();
      next_step = get_min_neighbour(new_cell, cur, arr, 1);
      path_queue.push(next_step);
      stack_flood.push(next_step);
      go_to_cell(angle_now, next_step.value);
      path_distance_value_find++;
    } else {
      log("empty Queue- break");
      break;
    }
    // std::cerr<<"cur:"<<cur.value<<"-dest:"<<dest.value<<std::endl;
  }
  while (!path_queue.empty()) path_queue.pop();
  // new_cell=update_walls(angle_now,cur.row,cur.col);

  std::cerr << "total_cost:" << path_distance_value_find << std::endl;
  coord p_return = {next_step.row, next_step.col, 0};
  return p_return;
}
void init_maze() {
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      maze.cells[i][j].visited = 0;
      maze.cells[i][j].angle_update = 90;
      maze.cells[i][j].dead = 0;
      for (int k = 0; k < 4; k++) maze.cells[i][j].walls[k] = 0;
    }
  }
}
void go_to_cell_shorted(int &angle, int dir) {
  int new_dir = dir;
  switch (angle) {
    case 90:
      break;
    case 270:
      if (dir % 2 == 0)
        new_dir += 1;
      else
        new_dir -= 1;
      break;
    case 0:
      if (dir == 0 || dir == 1)
        new_dir += 2;
      else if (dir == 2)
        new_dir = 1;
      else
        new_dir = 0;
      break;
    case 180:
      if (dir == 2 || dir == 3)
        new_dir -= 2;
      else if (dir == 0)
        new_dir = 3;
      else
        new_dir = 2;
      break;
  }
  go_to_cell(angle, new_dir);
}

std::queue<pair<int, int>> shorted_path_go(std::vector<std::vector<int>> &arr, int angle_now, coord start, coord dest)  // vẽ ra con đường ngắn nhất
{
  std::queue<int> next_dir_path;
  std::queue<pair<int, int>> shortest_path;

  cell_info new_cell;
  // cell_info new_cell;
  int save_row, save_col;
  coord cur = start;
  int angle = angle_now;
  for (int i = 0; i < arr[start.row][start.col]; i++) {
    int next_dir = -1;
    int newRow;
    int newCol;
    for (int dir = 0; dir < 4; ++dir) {
      newRow = cur.row + dy[dir];  // 0 0 -1 1
      newCol = cur.col + dx[dir];  // 1 -1 0 0
      bool check_ = maze.cells[cur.row][cur.col].walls[dir];
      if (isValid(newRow, newCol) && !check_) {
        if (arr[newRow][newCol] < arr[cur.row][cur.col]) {
          next_dir = dir;
          save_row = newRow;
          save_col = newCol;
        }
      }
    }
    if (next_dir != -1) {
      cur.row = save_row;
      cur.col = save_col;
      pair<int, int> steps;
      steps.first = save_row;
      steps.second = save_col;

      shortest_path.push(steps);

      next_dir_path.push(next_dir);
      API::setColor(save_row, save_col, 'g');
      std::cerr << save_row << save_col << endl;
      API::setText(save_row, save_col, std::to_string(arr[save_row][save_col]));
    }
  }
  return shortest_path;
}

/// @brief //////////////////////////////
int cur_position[2] = {0, 0};
int cur_direction = 0;
void update_position(int &cur_direction) {
  switch (cur_direction) {
    case 0:  // NORTH
      cur_position[1] += 1;
      break;
    case 1:  // EAST
      cur_position[0] += 1;
      break;
    case 2:  // SOUTH
      cur_position[1] -= 1;
      break;
    case 3:  // WEST
      cur_position[0] -= 1;
      break;
  }
}

void update_direction(int &cur_direction, int turn_direction) {
  cur_direction = (cur_direction + turn_direction) % 4;
  if (cur_direction < 0) {
    cur_direction += 4;
  }
}

std::string robot_commands;

void move_forward() {
  API::moveForward();
  update_position(cur_direction);
  // log("foward");
}

void turn_right() {
  API::turnRight();
  update_direction(cur_direction, 1);
  // log("Right");
}

void turn_left() {
  API::turnLeft();
  update_direction(cur_direction, -1);
  // log("Left");
}

void turn_around() {
  turn_right();
  turn_right();
  // log("Around");
}

void set_dir(int _dir) {
  if (_dir == cur_direction) {
    return;
  }
  if (_dir == (cur_direction + 1) % 4) {
    turn_right();
    return;
  }
  if (_dir == (cur_direction + 2) % 4) {
    turn_around();
    return;
  }
  turn_left();
  return;
}

int past_dir;
int turn_toward(int save_row, int save_col, int &cur_direction) {
  int _dir = cur_direction;
  if (cur_position[0] == save_row) {
    if (cur_position[1] - save_col == 1) {
      _dir = 2;
    } else {
      _dir = 0;
    }
  } else {
    if (cur_position[0] - save_row == 1) {
      _dir = 3;
    } else {
      _dir = 1;
    }
  }
  past_dir = cur_direction;
  set_dir(_dir);
  return _dir;
}

void exec_shortest_path(std::queue<pair<int, int>> shortest_path, int &cur_direction) {
  while (!shortest_path.empty()) {
    turn_toward(shortest_path.front().first, shortest_path.front().second, cur_direction);
    shortest_path.pop();
    if (cur_direction - past_dir == 1 || cur_direction - past_dir == -3) {
      robot_commands += "R";
      move_forward();
    } else if (cur_direction - past_dir == -1 || cur_direction - past_dir == 3) {
      robot_commands += "L";
      move_forward();
    } else {
      move_forward();
      robot_commands += "F";
    }
  }
  robot_commands += "S";
}



void start_path_finding(int min_goal_x, int min_goal_y) {
  std::vector<std::vector<int>> arr;
  init_arr(arr, rows, cols);
  init_flood(arr, min_goal_x, min_goal_y);
  init_maze();
  coord start = {0, 0, arr[0][0]};
  coord dest = {min_goal_x, min_goal_y, arr[min_goal_x][min_goal_y]};
  API::setColor(0, 0, 'r');
  API::setColor(min_goal_x, min_goal_y, 'r');
  API::setColor(min_goal_x, min_goal_y + 1, 'r');
  API::setColor(min_goal_x + 1, min_goal_y + 1, 'r');
  API::setColor(min_goal_x + 1, min_goal_y + 1, 'r');
  API::setText(0, 0, "Start");
  API::setText(7, 7, "Goal");
  update_wall_debug(arr);
  int angle_now = 90;
  coord new_coord;
  new_coord = floodfill(start, dest, arr, angle_now);
  init_flood_start(arr, 0, 0, 1);
  std::cerr << "done2" << std::endl;
  new_coord = floodfill(new_coord, start, arr, angle_now);
  init_flood_start(arr, min_goal_x, min_goal_y, 2);
  API::turnLeft();
  API::turnLeft();
  exec_shortest_path(shorted_path_go(arr, angle_now, new_coord, dest), cur_direction);
  std::cerr << robot_commands << endl;
}

int main(int argc, char *argv[]) {
  start_path_finding(7, 7);
  statemachine();
}
