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
#include "Server.hpp"
#include <iostream>
#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include "cereal/json.h"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
    printf("Running get file length");
 ifstream stream;
 stream.seekg(0, ios::end);
 int length = stream.tellg();
 return length;
}


void Server::initialize(unsigned int board, string p1_board, string p2_board){
    board_size = board;
    //printf("Running server initialize");
    if(board_size <= 0 || board_size > 10)
    {throw invalid_argument("Board size must be greater than zero.");}
    if(board_size == 10-1)
    {throw invalid_argument("Board size must be greater than zero.");}
    if(p1_board != "player_1.setup_board.txt")
    {throw invalid_argument("Bad file name");}
    if(p2_board != "player_2.setup_board.txt")
    {throw invalid_argument("Bad file name");}
    else{printf("Running server initialize");}
    //open two string files and assign them to corresponding if streams
    ifstream p1_setup_board(p1_board);
    ifstream p2_setup_board(p2_board);

    //create a 2 dimensional vector of size boardsize*boardsize dont actually have to do that
    //string board[board_size][board_size];

}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    printf("Running evaluate shot");
    if(player != 2 && player != 1)
    {throw invalid_argument("Bad player number");}
    //looks at the player set up board and determines the result
    //turns the text file into a string array here
    //string array[board_size];

    if (player == 1) {
        ifstream fin("player_1.setup_board.txt");
if (fin) {
    vector<string> board;
    string line;
    while (getline(fin, line)) {
        board.push_back(line);
    }


    //create the result file
    string s;
    s = board[x][y];
    string fname = {"player_1.result.txt"};
    // all of the stuff to fill the file
    unsigned int res;
    //if out of bounds
    if ((x > board_size - 1 || x < 0) || (y > board_size - 1 || y < 0)) {
        res = 0;
        ofstream array_result1(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_result1); // initialize an archive on the file
        write_archive(cereal::make_nvp("res", res)); // serialize the data giving it a name
        //string fdel = "player_1.shot.json";
        //remove(fdel.c_str());
        return OUT_OF_BOUNDS;
    }
    //if miss
    if (s != "_") {
        res = -1;
        ofstream array_result1(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_result1); // initialize an archive on the file
        write_archive(cereal::make_nvp("res", res)); // serialize the data giving it a name
        //string fdel = "player_1.shot.json";
        //remove(fdel.c_str());
        return MISS;
    }
        //if hit
    else {
        res = 1;
        ofstream array_result1(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_result1); // initialize an archive on the file
        write_archive(cereal::make_nvp("res", res)); // serialize the data giving it a name
        //string fdel = "player_1.shot.json";
        //remove(fdel.c_str());
        return HIT;
    }
    cout << res << endl;


    //delete shot file

}
        }
        if (player == 2) {
            ifstream fin("player_2.setup_board.txt");

if(fin) {
    vector<string> board;
    string line;
    while (getline(fin, line)) {
        board.push_back(line);
    }


    //create the result file
    string s;
    s = board[x][y];
    string fname = {"player_2.result.txt"};
    // all of the stuff to fill the file
    unsigned int res;
    //if out of bounds
    if ((x > board_size - 1 || x < 0) || (y > board_size - 1 || y < 0)) {
        res = 0;
        ofstream array_result1(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_result1); // initialize an archive on the file
        write_archive(cereal::make_nvp("res", res)); // serialize the data giving it a name
        //string fdel = "player_2.shot.json";
        //remove(fdel.c_str());
        return OUT_OF_BOUNDS;
    }
    //if miss
    if (s != "_") {
        res = -1;
        ofstream array_result1(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_result1); // initialize an archive on the file
        write_archive(cereal::make_nvp("res", res)); // serialize the data giving it a name
        //string fdel = "player_2.shot.json";
        //remove(fdel.c_str());
        return MISS;
    }
        //if hit
    else {
        res = 1;
        ofstream array_result1(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_result1); // initialize an archive on the file
        write_archive(cereal::make_nvp("res", res)); // serialize the data giving it a name
        //string fdel = "player_2.shot.json";
        //remove(fdel.c_str());
        return HIT;
    }
    cout << res << endl;


    //delete shot file
    string fdel = "player_2.shot.json";
    remove(fdel.c_str());
}

        }
    }




int Server::process_shot(unsigned int player) {
    printf("Running process shot");

    if(player != 2 && player != 1)
    {throw invalid_argument("Bad player number");}
    if(player == 1) {
        printf("player 1");
        ifstream array_fire1("player_1.shot.json");
        //check to see if shot file exists
        if (array_fire1) {
            //reads in x and y from json file
            unsigned int x, y;
            // deserialize the array
            cereal::JSONInputArchive read_archive(array_fire1); // initialize an archive on the file
            read_archive(x, y); // deserialize the array
            //array_fire1.close(); // close the file
if(x > board_size + 1 || x < 0){
    throw invalid_argument("Out of bounds shot");
}

            if(y > board_size + 1 || y < 0){
                throw invalid_argument("Out of bounds shot");
            }
            // x = x;
            //y = y;
            cout<< x << endl;
            cout << y << endl;
            //evaluate_shot(1, x, y);
            unsigned int res;
            string fname = {"player_1.result.txt"};
            if(evaluate_shot(1, x, y) == HIT){
                res = 1;
                ofstream array_result1(fname); // create an output file stream
                cereal::JSONOutputArchive write_archive(array_result1); // initialize an archive on the file
                write_archive(cereal::make_nvp("res", res)); // serialize the data giving it a name
                return SHOT_FILE_PROCESSED;
            }
            if(evaluate_shot(1, x, y) == MISS){
                res = -1;
                ofstream array_result1(fname); // create an output file stream
                cereal::JSONOutputArchive write_archive(array_result1); // initialize an archive on the file
                write_archive(cereal::make_nvp("res", res)); // serialize the data giving it a name
                return SHOT_FILE_PROCESSED;
            }
            if(evaluate_shot(1, x, y) == OUT_OF_BOUNDS){
                res = 0;
                ofstream array_result1(fname); // create an output file stream
                cereal::JSONOutputArchive write_archive(array_result1); // initialize an archive on the file
                write_archive(cereal::make_nvp("res", res)); // serialize the data giving it a name
            return SHOT_FILE_PROCESSED;
        }

        }
        else {
            return NO_SHOT_FILE;
        }
        string fdel = "player_1.shot.json";
        remove(fdel.c_str());

    }
        if (player == 2) {
            ifstream array_fire1("player_2.shot.json");
            //check to see if shot file exists
            if (array_fire1) {
                //reads in x and y from json file
                unsigned int x, y;
                // deserialize the array
                cereal::JSONInputArchive read_archive(array_fire1); // initialize an archive on the file
                read_archive(x, y); // deserialize the array
                //array_fire1.close(); // close the file
                if(x > board_size + 1 || x < 0){
                    throw invalid_argument("Out of bounds shot");
                }

                if(y > board_size + 1 || y < 0){
                    throw invalid_argument("Out of bounds shot");
                }
                // x = x;
                //y = y;
                cout<< x << endl;
                cout << y << endl;
                evaluate_shot(1, x, y);
                unsigned int res;
                string fname = {"player_2.result.txt"};
                if(evaluate_shot(1, x, y) == HIT){
                    res = 1;
                    ofstream array_result2(fname); // create an output file stream
                    cereal::JSONOutputArchive write_archive(array_result2); // initialize an archive on the file
                    write_archive(cereal::make_nvp("res", res)); // serialize the data giving it a name
                    return SHOT_FILE_PROCESSED;
                }
                if(evaluate_shot(1, x, y) == MISS){
                    res = -1;
                    ofstream array_result2(fname); // create an output file stream
                    cereal::JSONOutputArchive write_archive(array_result2); // initialize an archive on the file
                    write_archive(cereal::make_nvp("res", res)); // serialize the data giving it a name
                    return SHOT_FILE_PROCESSED;
                }
                if(evaluate_shot(1, x, y) == OUT_OF_BOUNDS){
                    res = 0;
                    ofstream array_result2(fname); // create an output file stream
                    cereal::JSONOutputArchive write_archive(array_result2); // initialize an archive on the file
                    write_archive(cereal::make_nvp("res", res)); // serialize the data giving it a name
                    return SHOT_FILE_PROCESSED;
                }

            }
            else {
                return NO_SHOT_FILE;
            }
            string fdel = "player_2.shot.json";
            remove(fdel.c_str());

        }

}
