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


void Server::initialize(unsigned int board_size, string p1_setup_board, string p2_setup_board){
    if(board_size <=0){throw invalid_argument("Board size must be greater than zero.");}
    if(p1_setup_board != "player_1.setup_board.txt"){throw invalid_argument("Bad file name");}
    if(p2_setup_board != "player_2.setup_board.txt"){throw invalid_argument("Bad file name");}
    //open two string files and assign them to corresponding if streams
    ifstream p1_board(p1_setup_board);
    ifstream p2_board(p2_setup_board);

    //create a 2 dimensional vector of size boardsize*boardsize dont actually have to do that
    //string board[board_size][board_size];

}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    printf("Running evaluate shot");
    //looks at the player set up board and determines the result
    //turns the text file into a string array here
    string array[board_size];
    if (player = 1) {
        string line;
        ifstream p1_board("player_1.setup_board.txt");
        short counter = 0;
        if (p1_board.is_open()) {
            while (!p1_board.eof()) {
                getline(p1_board, line);
                array[counter] = line;
                counter++;
            }
            p1_board.close();
        }
        // separate lines into an array and separate characters to populate board array
        string board[board_size][board_size];
        for (int i = 0; i < board_size - 1; i++) {
            string temp = array[i];
            char cstr[temp.size() + 1];
            strcpy(cstr, temp.c_str());
            for (int j = 0; j < board_size - 1; j++) {
                board[j][i] = cstr[j];
            }
        }
        string s = board[x][y];


        //create the result file
        string fname = {"player_1.result.txt"};
        // all of the stuff to fill the file
        int res;
        //if out of bounds
        if (x > board_size - 1 || y > board_size - 1) {
            res = OUT_OF_BOUNDS;
        }
        //if hit
        if (s != "_") {
            res = MISS;
        }
            //if miss
        else {
            res = HIT;
        }

        // serialize the file (does this have to be an array?)
        ofstream array_result1(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_result1); // initialize an archive on the file
        write_archive(cereal::make_nvp("result", res)); // serialize the data giving it a name
        //write_archive.finishNode(); // wait for the writing process to finish
        array_result1.close(); // close the file


        //delete shot file
        string fdel = "player_1.shot.json";
        remove(fdel.c_str());
    }
    if (player = 2) {
        string line;
        ifstream p2_board("player_2.setup_board.txt");
        short counter = 0;
        if (p2_board.is_open()) {
            while (!p2_board.eof()) {
                getline(p2_board, line);
                array[counter] = line;
                counter++;
            }
            p2_board.close();
        }
        // separate lines into an array and separate characters to populate board array
        string board[board_size][board_size];
        for (int i = 0; i < board_size - 1; i++) {
            string temp = array[i];
            char cstr[temp.size() + 1];
            strcpy(cstr, temp.c_str());
            for (int j = 0; j < board_size - 1; j++) {
                board[j][i] = cstr[j];
            }
        }
        string s = board[x][y];


        //create the result file
        string fname = {"player_1.result.txt"};
        // all of the stuff to fill the file
        int res;
        //if out of bounds
        if (x > board_size - 1 || y > board_size - 1) {
            res = OUT_OF_BOUNDS;
        }
        //if hit
        if (s != "_") {
            res = MISS;
        }
            //if miss
        else {
            res = HIT;
        }

        // serialize the file (does this have to be an array?)
        ofstream array_result2(fname); // create an output file stream
        cereal::JSONOutputArchive write_archive(array_result2); // initialize an archive on the file
        write_archive(cereal::make_nvp("result", res)); // serialize the data giving it a name
        //write_archive.finishNode(); // wait for the writing process to finish
        array_result2.close(); // close the file


        //delete shot file
        string fdel = "player_2.shot.json";
        remove(fdel.c_str());
    }

}


int Server::process_shot(unsigned int player) {
    printf("Running process shot");
    if(player == 1) {
        ifstream array_fire1("player_1.shot.json");
        //check to see if shot file exists
        if (array_fire1) {
            //reads in x and y from json file
            int x, y;
            //string fname = "player_1.shot.json";
            // create a two dimensional array for deserialization
            vector<unsigned int> input(2);

//            // deserialize the array
           //ifstream array_fire1(fname); // create an input file stream
           cereal::JSONInputArchive read_archive(array_fire1); // initialize an archive on the file
           read_archive(input); // deserialize the array
           array_fire1.close(); // close the file
//
            //x = input[0];
           // y = input[1];
           // printf("input[0] = %d, input[1] = %d\n", input[0], input[1]);
//            //calls evaluate shot with x an y
//            evaluate_shot(1, x, y);
//        }
//
//            // if no data- return no shot file
//        else {
//            return NO_SHOT_FILE;
        }
    }
    if(player == 2) {
        ifstream array_fire2("player_2.shot.json", ifstream::binary);
        //check to see if shot file exists
        if(array_fire2) {
            //reads in x and y from json file
            int x, y;
            string fname = "player_2.shot.json";
            // create a two dimensional array for deserialization
            vector<int> input(2);

            // deserialize the array
            ifstream array_res2(fname); // create an input file stream
            cereal::JSONInputArchive read_archive(array_res2); // initialize an archive on the file
            read_archive(input); // deserialize the array
            array_res2.close(); // close the file
            x = input[0];
            y = input[1];
            //calls evaluate shot with x an y
            evaluate_shot(1, x, y);
        }

            // if no data- return no shot file
        else {
            return NO_SHOT_FILE;
        }
    }

}