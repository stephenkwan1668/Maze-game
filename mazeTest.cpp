# include <iostream>
# include <vector>
# include <fstream>

using namespace std;

class InputFile{

public:
    ifstream inFS;
    int rowSize,collumnSize;
    int exitrow,exitcollumn;
    int playerStartRow,playerStartCollumn;
    string movementSet;


    template<class T>T  Getfile(int& argc, T& argv) {
        string fileName = "RAT.txt";
//        if (argc <2){
//            throw runtime_error("an error occured: no input file name given");
//        }
//
//        fileName = argv[1];
        inFS.open(fileName);

        if (!inFS.is_open()) {
            throw runtime_error("an error occured: could not open input file " + fileName);
        }

    }

    pair<int,int> GetMazeSize() {
        inFS >> rowSize;
        inFS >> collumnSize;

        if(inFS.fail()){
            throw runtime_error("an error occurred: could not read height and width of the maze");
        }

        return make_pair(rowSize,collumnSize);
    }


    string GetMazePattern() {
        string mazeInput;
        string temp = "";
        int i = 0;

        if(!inFS.fail()) {
            while (i < rowSize) {
                inFS >> temp;
                i++;
                mazeInput += temp;
            }
        }
        else{
            throw runtime_error("an error occurred: could not read maze layout");
        }
        return mazeInput;
    }


    pair<int,int> GetExitCoordinates() {
        inFS >> exitrow;
        inFS >> exitcollumn;

        if(inFS.fail()){
            throw runtime_error("an error occurred: an error occurred: could not read coordinates");
        }

        return make_pair(exitrow,exitcollumn);
    }


    pair<int,int> GetStartCoordinates() {
        inFS >> playerStartRow;
        inFS >> playerStartCollumn;

        if(inFS.fail()){
            throw runtime_error("an error occurred: an error occurred: could not read coordinates");
        }

        return make_pair(playerStartRow,playerStartCollumn);
    }


    string GetMovementSet(){
        inFS >> movementSet;

        return movementSet;
    }

};


class Maze{
public:

    vector<vector<char> > maze;

    void ApplySize(int rowSize,int collumnSize){

        maze = vector<vector<char> >( rowSize , vector<char> (collumnSize));

    }


    void InsertMazePattern(string mazeInput,int rowSize,int collumnSize) {

        for (int i = 0; i < mazeInput.size(); i++) {
            if (mazeInput.at(i) == 'l' || mazeInput.at(i) == '.') {
                int counterInput = 0;
                for (int i = 0; i < rowSize; i++) {
                    for (int j = 0; j < collumnSize; j++) {
                        maze.at(i).at(j) = mazeInput.at(counterInput);
                        counterInput++;
                    }
                }
            }
            else{
                throw runtime_error("an error occurred: could not read maze layout");
            }
        }

        if (mazeInput.size() / collumnSize != rowSize){
            throw runtime_error("an error occurred: could not read maze layout");
        }

    }


    void insertExit(int exitRow, int exitCollumn){
        if (maze.at(exitRow).at(exitCollumn) = '.') {
            maze.at(exitRow).at(exitCollumn) = 'x';
        }
        else{
            cout << "an error occurred: exit outside maze or off the path" << endl;
        }
    }


    void insertStart(int startRow, int startCollumn){
        if (maze.at(startRow).at(startCollumn) = '.') {
            maze.at(startRow).at(startCollumn) = 'P';
        }
        else{
            cout << "an error occurred: player outside maze or off the path" << endl;
        }
    }


    void Show(int rowSize,int collumnSize) {

        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < collumnSize; j++) {
                cout << maze.at(i).at(j);
            }
            cout << endl;
        }

    }

};


class MovementAndCheck{
public:

    vector<vector<char> > currentPlayerPosition;


    void InitializePositionUpdater(int& mazeRows, int& mazeCollums){
        currentPlayerPosition = vector<vector<char> >( mazeRows , vector<char> (mazeCollums));
    }


    int Movement(string& movementSet, vector<vector<char> >& maze,int startRow, int startCollumn,
                int& updatedPositionRow,int& updatedPositionCollumn) {

        for (int i = 0; i < movementSet.size(); i++) {
            if (movementSet.at(i) == 'l'
                || movementSet.at(i) == 'r'
                || movementSet.at(i) == 'u'
                || movementSet.at(i) == 'd') {

                if (movementSet.at(i) == 'l'){
                    updatedPositionCollumn = updatedPositionCollumn - 1;
                    currentPlayerPosition.at(updatedPositionRow).at(updatedPositionCollumn) = 'P';

                } else if (movementSet.at(i) == 'r'){
                    updatedPositionCollumn = updatedPositionCollumn + 1;
                    currentPlayerPosition.at(updatedPositionRow).at(updatedPositionCollumn) = 'P';

                } else if (movementSet.at(i) == 'u'){
                    updatedPositionRow = updatedPositionRow - 1;
                    currentPlayerPosition.at(updatedPositionRow).at(updatedPositionCollumn) = 'P';

                } else if (movementSet.at(i) == 'd'){
                    updatedPositionRow = updatedPositionRow + 1;
                    currentPlayerPosition.at(updatedPositionRow).at(updatedPositionCollumn) = 'P';
                }

            }
            else {
                throw runtime_error("an error occurred: an error occurred: could not read coordinates");
            }
        }
        return updatedPositionRow,updatedPositionCollumn;
    }


    bool WinOrLose(vector<vector<char> >& maze,int& exitRow, int& exitCollumn,int& updatedPositionRow,int& updatedPositionCollumn){

    if (updatedPositionRow == exitRow && updatedPositionCollumn == exitCollumn) {

        maze.Show(exitRow, exitCollumn);


        return true;
    }
    else{
        cout << "\n The player did not reach the exit." << endl;
        return false;
    }

    }


    void CheckCollition(vector<vector<char> >& pathMaze, int rowSize, int collumnSize){

        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < collumnSize; j++) {
                if (currentPlayerPosition.at(i).at(j) == 'P') {
                    if (pathMaze.at(i).at(j) != '.') {
                        throw runtime_error("an error occurred: an error occurred: could not read coordinates");
                    }
                }
            }
        }
    }


    void Show(int rowSize,int collumnSize) {

        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < collumnSize; j++) {
                cout << currentPlayerPosition.at(i).at(j);
            }
            cout << endl;
        }

    }


};


int main(int argc, char* argv[]) {
    try {
////variable declaration
        int mazeRows, mazeCollums;
        int exitRow, exitCollumn;
        int startRow, startCollumn;
        int updatedPositionRow, updatedPositionCollumn;

        string pattern, movementSet;

////get and read file
        InputFile input;

        input.Getfile(argc, argv);

        pair<int, int> mazeSizedimension = input.GetMazeSize();
        mazeRows = mazeSizedimension.first;
        mazeCollums = mazeSizedimension.second;

        pattern = input.GetMazePattern();


        pair<int, int> exitcoordinate = input.GetExitCoordinates();
        exitRow = exitcoordinate.first;
        exitCollumn = exitcoordinate.second;


        pair<int, int> startcoordinate = input.GetStartCoordinates();
        startRow = startcoordinate.first;
        startCollumn = startcoordinate.second;

        input.GetMovementSet();


////define maze /w exit and start 'P'
        Maze maze;
        maze.ApplySize(mazeRows, mazeCollums);
        maze.InsertMazePattern(pattern, mazeRows, mazeCollums);
        maze.insertExit(exitRow, exitCollumn);
        maze.insertStart(startRow, startCollumn);
        maze.Show(mazeRows, mazeCollums);
cout<< endl;

////define new maze(name:mazePath) w/o exit and start to compare player coordinates
        Maze pathMaze;
        pathMaze.ApplySize(mazeRows, mazeCollums);
        pathMaze.InsertMazePattern(pattern, mazeRows, mazeCollums);
        pathMaze.Show(mazeRows, mazeCollums);
cout<<endl;

////Initialization of object and position updater:
        MovementAndCheck movementAndCheck;
        movementAndCheck.InitializePositionUpdater(mazeRows, mazeCollums);

        updatedPositionRow = startRow;
        updatedPositionCollumn = startCollumn;

////Movement of 'P'
        movementAndCheck.Movement(movementSet, maze.maze, startRow, startCollumn, updatedPositionRow,
                                  updatedPositionCollumn);

////Check collition between mazePath and currentPlayerPosition
        movementAndCheck.CheckCollition(pathMaze.maze, mazeRows, mazeCollums);

////Check win or lose condition
        movementAndCheck.WinOrLose(maze.maze, exitRow, exitCollumn, updatedPositionRow, updatedPositionCollumn);

////print maze,start and exit area
        maze.Show(mazeRows, mazeCollums);
        movementAndCheck.Show(mazeRows, mazeCollums);
    }

    catch (runtime_error &excpt) {
        cout << excpt.what();
    }

    return 0;
}


