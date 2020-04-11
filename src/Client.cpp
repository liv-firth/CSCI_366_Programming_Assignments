//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "common.hpp"
#include "Client.hpp"
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include "cereal/json.h"



Client::~Client() {
    //constructor a player, 2 will need to run in parallel
   // wont need any code
    string fname = "player_1.action_board.json";
    //remove any existing files
    remove(fname.c_str());
    string cname = "player_2.action_board.json";
    //remove any existing files
    remove(cname.c_str());
}


void Client::initialize(unsigned int play, unsigned int board_size){
    printf("Running initialize");
    //assigns player number
    player = play;
    //builds action board (JSON) file based on board size (name of file depends on the two if statement)
    if(player == 1) {
        //to assign text file name correctly
        string fname = "player_1.action_board.json";
        //remove any existing files
        remove(fname.c_str());
        //make a vector
        vector<vector<int> > array1 (board_size, vector<int>(board_size,0 ));
        //cerealize
        ofstream array_ab2(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_ab2); // initialize an archive on the file
        write_archive(cereal::make_nvp("board", array1)); // serialize the data giving it a name

    }

    else if(player == 2){

        string fname = "player_2.action_board.json";

        remove(fname.c_str());

        vector<vector<int> > array1 (board_size, vector<int>(board_size, 0));

        //cerealize
        ofstream array_ab2(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_ab2); // initialize an archive on the file
        write_archive(cereal::make_nvp("board", array1)); // serialize the data giving it a name

    }
    initialized = true;
}


void Client::fire(unsigned int inputX, unsigned int inputY) {
    printf("Running fire");
    // creates json shot file
    if(player ==1) {
        printf("player 1, fire");
        string fname = "player_1.shot.json";
        // transfers input x and y into file
        unsigned int x = inputX;
        unsigned int y = inputY;
        //cerealize
        ofstream array_ab2(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_ab2); // initialize an archive on the file
        write_archive(cereal::make_nvp("x", x),cereal::make_nvp("y", y) ); // serialize the data giving it a name

    }
    if(player ==2){
        string fname = "player_2.shot.json";
        // transfers input x and y into file
        unsigned int x = inputX;
        unsigned int y = inputY;
        //cerealize
        ofstream array_ab2(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_ab2); // initialize an archive on the file
        write_archive(cereal::make_nvp("x", x),cereal::make_nvp("y", y) ); // serialize the data giving it a name


    }

}


bool Client::result_available() {
    printf("Running result available");
    // listens/waits for the result file to exist
    // returns a boolean value
    if(player == 1) {
        ifstream array_result1("player_1.result.json", ifstream::binary);
        if (array_result1) {
            cout << "The file exists" << endl;
            return true;
        }

        else { return false; }
    }
    if(player == 2) {
        ifstream array_result2("player_2.result.json", ifstream::binary);
        if (array_result2) {
            cout << "The file exists" << endl;
            return true;
        }

        else { return false; }
    }
}


int Client::get_result() {
    printf("Running get result");
    // reads result file
    // returns result (as an int [HIT, MISS, OUT OF BOUNDS])
    if (player == 1) {
        ifstream array_result1("player_1.result.json");
        //check to see if shot file exists
        if (array_result1) {
            //reads in x and y from json file
            signed int res;
            // deserialize the array
            cereal::JSONInputArchive read_archive(array_result1); // initialize an archive on the file
            read_archive(res); // deserialize the array
            cout << res << endl;
            if (res != 0 && res != 1 && res != -1) { throw invalid_argument("Bad result."); }
            //HIT
            if (res == HIT) {
                string cname = "player_1.result.json";
                //remove any existing files
                remove(cname.c_str());
                return HIT;
            }
                //MISS
            else if (res == MISS) {
                string cname = "player_1.result.json";
                //remove any existing files
                remove(cname.c_str());
                return MISS;
            }
                //OUT OF BOUNDS
            else if (res == OUT_OF_BOUNDS) {
                string cname = "player_1.result.json";
                //remove any existing files
                remove(cname.c_str());
                return OUT_OF_BOUNDS;
            }
            string fname = "player_1.result_board.json";
            // remove any old serialization files
            //remove(fname.c_str());
        }
    }

        if (player == 2) {
            ifstream array_result1("player_2.result.json");
            //check to see if shot file exists
            if (array_result1) {
                //reads in x and y from json file
                signed int res;
                // deserialize the array
                cereal::JSONInputArchive read_archive(array_result1); // initialize an archive on the file
                read_archive(res); // deserialize the array
                cout << res << endl;
                if (res != 0 && res != 1 && res != -1) { throw invalid_argument("Bad result."); }
                //HIT
                if (res == HIT) {
                    string cname = "player_2.result.json";
                    //remove any existing files
                    remove(cname.c_str());
                    return HIT;
                }
                    //MISS
                else if (res == MISS) {
                    string cname = "player_2.result.json";
                    //remove any existing files
                    remove(cname.c_str());
                    return MISS;
                }
                    //OUT OF BOUNDS
                else if (res == OUT_OF_BOUNDS) {
                    string cname = "player_2.result.json";
                    //remove any existing files
                    remove(cname.c_str());
                    return OUT_OF_BOUNDS;
                }

            }


        }

}


void Client::update_action_board(int result, unsigned int x, unsigned int y) {
    printf("Running update action board");
    //updates player action board
    if(player == 1) {
        string fname = "player_1.action_board.json";
        //create an array
        vector<vector<int> > array1 (board_size, vector<int>(board_size,0 ));
        //deserialize
        ifstream array_ifp(fname); // create an input file stream
        cereal::JSONInputArchive read_archive(array_ifp); // initialize an archive on the file
        read_archive(array1); // deserialize the array
        array_ifp.close(); // close the file
        //update the board
        //hit
        if (result == 1) {

            array1[x][y] = 1;
        }
            //miss
        else if (result == -1) {
            array1[x][y] = -1;
        }
        //serialize
        ofstream array_ab1(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_ab1); // initialize an archive on the file
        write_archive(cereal::make_nvp("board", array1)); // serialize the data giving it a name
        //write_archive.finishNode(); // wait for the writing process to finish
        //array_ab1.close(); // close the file
    }
    if(player == 2) {
        string fname = "player_2.action_board.json";
        //create an array
        vector<vector<int> > array1 (board_size, vector<int>(board_size,0 ));
        //deserialize
        ifstream array_ifp2(fname); // create an input file stream
        cereal::JSONInputArchive read_archive(array_ifp2); // initialize an archive on the file
        read_archive(array1); // deserialize the array
        array_ifp2.close(); // close the file
        //update the board
        //hit
        if (result == 1) {

            array1[x][y] = 1;
        }
            //miss
        else if (result == -1) {
            array1[x][y] = -1;
        }
        //serialize
        ofstream array_ab2(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_ab2); // initialize an archive on the file
        write_archive(cereal::make_nvp("board", array1)); // serialize the data giving it a name
        //write_archive.finishNode(); // wait for the writing process to finish
        //array_ab2.close(); // close the file
    }

}


string Client::render_action_board() {
    printf("Running render action board");
    // prints opposite players action board (where they have already fired/hit)
    if (player == 1) {
    string fname = "player_1.action_board.json";
    //create an array
        vector<vector<int> > array1 (board_size, vector<int>(board_size,0 ));
    //deserialize
    ifstream array_ab1(fname); // create an input file stream
    cereal::JSONInputArchive read_archive(array_ab1); // initialize an archive on the file
    read_archive(array1); // deserialize the array
    array_ab1.close(); // close the file

    for (int i = 0; i < board_size - 1; i++) {
        printf("\n");
        for (int j = 0; j < board_size - 1; j++) {
            printf("array[i][j] = %d", array1[i][j]);
        }
    }
}
    if (player == 2) {
        string fname = "player_2.action_board.json";
        //create an array
        vector<vector<int> > array1 (board_size, vector<int>(board_size,0 ));
        //deserialize
        ifstream array_ab2(fname); // create an input file stream
        cereal::JSONInputArchive read_archive(array_ab2); // initialize an archive on the file
        read_archive(array1); // deserialize the array
        array_ab2.close(); // close the file

        for (int i = 0; i < board_size - 1; i++) {
            printf("\n");
            for (int j = 0; j < board_size - 1; j++) {
                printf("array[i][j] = %d", array1[i][j]);
            }
        }
    }
}



