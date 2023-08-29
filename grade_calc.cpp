#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sstream>
#include<vector>
#include<algorithm>

using namespace std;

//Get index of the lowest grade
vector<int> indexOfMin(vector<vector<double>> grades) {
	vector<int> a; 
	int minIndex;
	for(int i = 0; i < grades.size(); i++) {
        minIndex = distance(grades[i].begin(), min_element(grades[i].begin(), grades[i].end()));
		a.push_back(minIndex); 
    }
	return a; 
}

//Converts point grade to percent grade
vector<vector<double>> percentGrade(vector<vector<double>> points, vector<int> header) {
	double result;
	vector<double> resultArr;
	vector<vector<double>> a; 
	for(int i = 0; i < points.size(); i++) {
        for(int j = 0; j < points[i].size(); j++) {
            result = (double)points[i][j] / header[j];
            resultArr.push_back(result);
        }
        a.push_back(resultArr);
        resultArr.clear();
    }
	return a; 
}

//Calculates points possible after the drop
vector<double> pointsPossible(vector<vector<double>> points, vector<int> header, vector<int> minIndexes) {
    vector<double> resultArr;
    for(int i = 0; i < points.size(); i++) {
		double result = 0 - header[minIndexes[i]];
        for(int j = 0; j < points[i].size(); j++) {
			result += header[j];	
		}
		resultArr.push_back(result); 
    }
    return resultArr;
}

//Calculates each students total points after the drop  
vector<double> pointsEarned(vector<vector<double>> points, vector<int> minIndexes) {
	vector<double> resultArr;
	for(int i = 0; i < points.size(); i++) {
        double result = 0 - points[i][minIndexes[i]];
		for(int j = 0; j < points[i].size(); j++) {
            result += points[i][j];
        }
        resultArr.push_back(result);
    }
    return resultArr;
}

int main(int argc, char **argv) {
	clock_t start, end; 

	ifstream fin;
    ofstream fout;

    string inputFile = string(argv[1]);
    string outputFile = string(argv[2]);

    vector<string> names;
    vector<int> header;
	vector<int> minIndexes; 
    vector<vector<double>> points;
    vector<vector<double>> grades;
	vector<double> studentPoints; 
	vector<double> totalPoints;

    vector<double> lines;
    string line;
    string name;
    string input;
    int num;

	//Start timing 
	start = clock(); 

	//Opens input file and creates an output file
    fin.open(inputFile);
    fout.open(outputFile);
 
	//Gets info from header and stores it in different data type vectors  
    getline(fin, line);
	istringstream sin(line); 
	getline(sin, name, ','); 
	names.push_back(name);
	while(getline(sin, input, ',')) {
		num = stoi(input); 
		header.push_back(num); 
	}
 
	//Get info from rest of file stores it in different data type vectors  
	while(getline(fin, line)) {
		istringstream sin(line);
		getline(sin, name, ',');
		names.push_back(name);

		while(getline(sin, input, ',')) {
			num = stoi(input);
			lines.push_back(num);
		}
		points.push_back(lines);
		lines.clear(); 
	}

	//Grab results of the integer calculations 
    grades = percentGrade(points, header); 
	minIndexes = indexOfMin(grades);
	totalPoints = pointsPossible(points, header, minIndexes); 
	studentPoints = pointsEarned(points,minIndexes);

	//Write to file 
	fout << "name,points_earned,points_possible" << endl;
	for(int i = 0; i < points.size(); i++) {
		fout << names[i + 1] << ',' << studentPoints[i] << ',' << totalPoints[i] << endl; 
	}

	//Ends timing and gives runtime  
	end = clock(); 
	double runTime = ((double)(end - start)) / CLOCKS_PER_SEC;
	cout << "The run time was: " << runTime << " seconds." << endl; 

	fin.close(); 
    fout.close();
    return 0;
}
