//
//  CS320 Project2.cpp
//  
//
//  Created by Dylan Ferrara on 11/17/15.
//
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "DirectMapped.hpp"
#include "SetAssociative.hpp"
#include "FullyAssociative.hpp"

using namespace std;

int totalAccesses = 0;

int main(int arg, char *args[]) {
    unsigned long long addr;
    string instr;
    
    if (arg != 3) {
        cerr << "ERROR: Needs Input and Output files" << endl;
        return 0;
    }
    
    ifstream infile(args[1]);
    ofstream outfile(args[2]);
    
    DirectMapped d1(32, 1);
    DirectMapped d2(32, 4);
    DirectMapped d3(32, 16);
    DirectMapped d4(32, 32);
    
    SetAssociative s1(2, 32, 16);
    SetAssociative s2(4, 32, 16);
    SetAssociative s3(8, 32, 16);
    SetAssociative s4(16, 32, 16);
    
    FullyAssociative f1(32, 16);
    FullyAssociative f2(32, 16);
    
    SetAssociative s5(2, 32, 16);
    SetAssociative s6(4, 32, 16);
    SetAssociative s7(8, 32, 16);
    SetAssociative s8(16, 32, 16);
    
    SetAssociative s9(2, 32, 16);
    SetAssociative s10(4, 32, 16);
    SetAssociative s11(8, 32, 16);
    SetAssociative s12(16, 32, 16);
    
    SetAssociative s13(2, 32, 16);
    SetAssociative s14(4, 32, 16);
    SetAssociative s15(8, 32, 16);
    SetAssociative s16(16, 32, 16);
    
    while (infile >> instr) {
        infile >> hex >> addr;
        
        d1.simulate(instr, addr);
        d2.simulate(instr, addr);
        d3.simulate(instr, addr);
        d4.simulate(instr, addr);
        
        s1.simulateLRU(instr, addr);
        s2.simulateLRU(instr, addr);
        s3.simulateLRU(instr, addr);
        s4.simulateLRU(instr, addr);
        
        f1.simulateLRU(instr, addr);
        f2.simulateHC(instr, addr);
        
        s5.simulateNoAloe(instr, addr);
        s6.simulateNoAloe(instr, addr);
        s7.simulateNoAloe(instr, addr);
        s8.simulateNoAloe(instr, addr);
        
        s9.simulateNLP(instr, addr);
        s10.simulateNLP(instr, addr);
        s11.simulateNLP(instr, addr);
        s12.simulateNLP(instr, addr);
        
        s13.simulatePoM(instr, addr);
        s14.simulatePoM(instr, addr);
        s15.simulatePoM(instr, addr);
        s16.simulatePoM(instr, addr);
        
        totalAccesses++;
    }
    
    //DirectMapped
    outfile << d1.cacheHits << "," << totalAccesses << "; " << d2.cacheHits << "," << totalAccesses << "; " << d3.cacheHits << "," << totalAccesses << "; " << d4.cacheHits << "," << totalAccesses << ";\n";
    
    //SetAssociative LRU
    outfile << s1.cacheHits << "," << totalAccesses << "; " << s2.cacheHits << "," << totalAccesses << "; " << s3.cacheHits << "," << totalAccesses << "; " << s4.cacheHits << "," << totalAccesses << ";\n";
    
    //FullyAssociative LRU
    outfile << f1.cacheHits << "," << totalAccesses << ";\n";
    
    //FullyAssociative Hot_Cold
    outfile << f2.cacheHits << "," << totalAccesses << ";\n";
    
    //SetAssociative No Allocation on Miss
    outfile << s5.cacheHits << "," << totalAccesses << "; " << s6.cacheHits << "," << totalAccesses << "; " << s7.cacheHits << "," << totalAccesses << "; " << s8.cacheHits << "," << totalAccesses << ";\n";
    
    //SetAssociative Next-Line Prefecting
    outfile << s9.cacheHits << "," << totalAccesses << "; " << s10.cacheHits << "," << totalAccesses << "; " << s11.cacheHits << "," << totalAccesses << "; " << s12.cacheHits << "," << totalAccesses << ";\n";
    
    //SetAssociative Prefect on a Miss
    outfile << s13.cacheHits << "," << totalAccesses << "; " << s14.cacheHits << "," << totalAccesses << "; " << s15.cacheHits << "," << totalAccesses << "; " << s16.cacheHits << "," << totalAccesses << ";\n";
    
    infile.close();
    outfile.close();
    
    return 0;
}