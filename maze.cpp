# include <iostream>
# include <vector>
# include <fstream>

using namespace std;

////reads data from file
class InputFile{

public:
    ifstream inFS;
    int rowSize, collumnSize;
    int exitRow, exitCollumn;
    int startRow, startCollumn;
    string movementSet, pattern;


    template<class T>T  Getfile(int& argc, T& argv) {
        string fileName;

        if (argc <2){
            throw runtime_error("no input file name given");
        }

        fileName = argv[1];
        inFS.open(fileName);

        if (!inFS.is_open()) {
            throw runtime_error("could not open input file " + fileName);
        }
    }


    int GetMazeSize() {
        inFS >> rowSize;
        inFS >> collumnSize;

        if(inFS.fail()){
            throw runtime_error("could not read height and width of the maze");
        }


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
            throw runtime_error("could not read maze layout");
    }

        if (mazeInput.size() / collumnSize != rowSize){
            throw runtime_error("could not read maze layout");
        }
        pattern = mazeInput;

}


    int GetExitCoordinates() {
        inFS >> exitRow;
        inFS >> exitCollumn;

        if(inFS.fail()){
            throw runtime_error("could not read coordinates");
        }

    }


    int GetStartCoordinates() {
        inFS >> startRow;
        inFS >> startCollumn;

        if(inFS.fail()){
            throw runtime_error("could not read coordinates");
        }

    }


    string GetMovementSet(){
        inFS >> movementSet;

        return movementSet;
    }

};

////intitalization of maze and print function
class Maze{
public:

    vector<vector<char> > maze;

    void ApplySize(InputFile& input){

        maze = vector<vector<char> >( input.rowSize , vector<char> (input.collumnSize));

    }


    void InsertMazePattern(InputFile& input) {

        for (int i = 0; i < input.pattern.size(); i++) {
            if (input.pattern.at(i) == 'l' || input.pattern.at(i) == '.') {
                int counterInput = 0;
                for (int i = 0; i < input.rowSize; i++) {
                    for (int j = 0; j < input.collumnSize; j++) {
                        maze.at(i).at(j) = input.pattern.at(counterInput);
                        counterInput++;
                    }
                }
            }
            else{
                throw runtime_error("could not read maze layout");
            }
        }



    }


    void insertExit(InputFile& input){

        if (maze.at(input.exitRow).at(input.exitCollumn) == '.') {
            maze.at(input.exitRow).at(input.exitCollumn) = 'x';
        }
        else{
            throw runtime_error( "exit outside maze or off the path");
        }
    }


    void insertStart(InputFile& input){

        if (maze.at(input.startRow).at(input.startCollumn) == '.') {
            maze.at(input.startRow).at(input.startCollumn) = 'P';
        }
        else{
            throw runtime_error( "INSERT PROBLEM: player outside maze or off the path");
        }
    }


    void Show(InputFile& input) {

        for (int i = 0; i < input.rowSize; i++) {
            for (int j = 0; j < input.collumnSize; j++) {
                cout << maze.at(i).at(j);
            }
            cout << endl;
        }

    }

};

////handles the players movement and check collition, wincondition,
class MovementAndCheck{
public:

////initialize player movement container, playersrow and playerscollumn variable
    vector<vector<char> > currentPlayerPosition;
    int updatedPositionRow, updatedPositionCollumn ;

    void InitializePositionUpdater(InputFile& input){
        currentPlayerPosition = vector<vector<char> >( input.rowSize , vector<char> (input.collumnSize));
    }


    int Movement(InputFile& input, vector<vector<char> >& maze) {

        for (int i = 0; i < input.movementSet.size(); i++) {
            if (input.movementSet.at(i) == 'l'
                || input.movementSet.at(i) == 'r'
                || input.movementSet.at(i) == 'u'
                || input.movementSet.at(i) == 'd') {

                if (input.movementSet.at(i) == 'l'){
                    updatedPositionCollumn = updatedPositionCollumn - 1;

                } else if (input.movementSet.at(i) == 'r'){
                    updatedPositionCollumn = updatedPositionCollumn + 1;

                } else if (input.movementSet.at(i) == 'u'){
                    updatedPositionRow = updatedPositionRow - 1;

                } else if (input.movementSet.at(i) == 'd'){
                    updatedPositionRow = updatedPositionRow + 1;
                }
                currentPlayerPosition.at(updatedPositionRow).at(updatedPositionCollumn) = 'P';
            }
            else {
                throw runtime_error("invalid move");
            }
        }
        return updatedPositionRow,updatedPositionCollumn;
    }


    void CheckWin(InputFile& input,Maze& pathMaze, Maze& maze,MovementAndCheck& movementAndCheck){

        if (updatedPositionRow == input.exitRow && updatedPositionCollumn == input.exitCollumn) {
            maze.Show(input);

            cout << endl;

            pathMaze.maze.at(movementAndCheck.updatedPositionRow).at(movementAndCheck.updatedPositionCollumn) = 'P';
            pathMaze.maze.at(input.startRow).at(input.startCollumn) = '.';
            pathMaze.Show(input);

            cout << "\nThe player reached the exit!" << endl;
        }
        else{
            maze.Show(input);

            cout << endl;

            pathMaze.maze.at(movementAndCheck.updatedPositionRow).at(movementAndCheck.updatedPositionCollumn) = 'P';
            pathMaze.maze.at(input.startRow).at(input.startCollumn) = '.';
            pathMaze.maze.at(input.exitRow).at(input.exitCollumn) = 'x';
            pathMaze.Show(input);

            cout << "\nThe player did not reach the exit." << endl;
        }

    }


    void CheckCollition(vector<vector<char> >& pathMaze, Maze& maze,InputFile& input){

        for (int i = 0; i < input.rowSize; i++) {
            for (int j = 0; j < input.collumnSize; j++) {
                if (currentPlayerPosition.at(i).at(j) == 'P') {
                    if (pathMaze.at(i).at(j) != '.') {
                        maze.Show(input);
                        cout << endl;
                        throw runtime_error("player outside maze or off the path");
                    }
                }
            }
        }
    }


};


int main(int argc, char* argv[]) {

    try{
////Get data from file and stores data in the global variables.
    InputFile input;

    input.Getfile(argc, argv);
    input.GetMazeSize();
    input.GetMazePattern();
    input.GetExitCoordinates();
    input.GetStartCoordinates();
    input.GetMovementSet();

////define maze /w exit location and start location
    Maze maze;
    maze.ApplySize(input);
    maze.InsertMazePattern(input);
    maze.insertExit(input);
    maze.insertStart(input);

////define new maze(name:mazePath) w/o exit and start to compare player coordinates
    Maze pathMaze;
    pathMaze.ApplySize(input);
    pathMaze.InsertMazePattern(input);

////Initialization of object
    MovementAndCheck movementAndCheck;
    movementAndCheck.InitializePositionUpdater(input);

////store start position in the player position:
    movementAndCheck.updatedPositionRow = input.startRow;
    movementAndCheck.updatedPositionCollumn = input.startCollumn;

////Movement of 'P'/player
    movementAndCheck.Movement(input, maze.maze);

////Check collition between mazePath and currentPlayerPosition
    movementAndCheck.CheckCollition(pathMaze.maze, maze, input);

////Check win or lose condition and print maze.
        movementAndCheck.CheckWin(input, pathMaze, maze, movementAndCheck);


}

catch (runtime_error &excpt) {
    cout << "an error occurred: " << excpt.what();
}

return 0;
}


