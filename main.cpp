#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include <queue>
#include<windows.h>

using namespace std;

class Messages
{
public:

	string messageid;
	int priority;
	string source_address;
	string destination_address;
	string payload;
	string trace;

	//Default Constrctor
	Messages()
	{
		messageid = " ";
		priority = 0;
		source_address = " ";
		destination_address = " ";
		payload = " ";
		trace = " ";
	}

	// Parametrized Constructor
	Messages(string id, int p, string sa, string da, string payl, string t)
	{
		messageid = id;
		priority = p;
		source_address = sa;
		destination_address = da;
		payload = payl;
		trace = t;
	}


	//Displaying Message details
	void DisplayDetails()
	{
		cout << "Id of Message: ";
		cout << messageid;
		cout << endl;
		cout << "Priority of Message: ";
		cout << priority;
		cout << endl;
		cout << "Source address of Message: ";
		cout << source_address;
		cout << endl;
		cout << "Destination address of Message: ";
		cout << destination_address;
		cout << endl;
		cout << "PayLoad of Message: ";
		cout << payload;
		cout << endl;
	}


	//Reading Details from the file 
	void ReadMessages(string id)
	{
		cout << "Input the Id of the Message you want to Read:";
		cin >> id;
		bool check = false;
		ifstream file("Messages.txt");
		if (!file.is_open())
		{
			cout << "Can not Open the File ";
			cout << endl;
			return;
		}
		while (file >> messageid >> priority >> source_address >> destination_address >> payload >> trace)
		{

			if (messageid == id)
			{
				check = true;
				Messages M(messageid, priority, source_address, destination_address, payload, trace);
				cout << endl;
				M.DisplayDetails();
				cout << endl;
			}
			else
			{
				cout << "Id doesn't match";
				cout << endl;
			}
		}
		file.close();
	}


	//Take input from the terminal and write into file
	void InputMessages()
	{
		ofstream file("Messages.txt", ios::app);
		if (!file.is_open())
		{
			cout << "Can not open the File ";
			cout << endl;
			return;
		}
		cout << "Input Details of Message ";
		cout << endl;
		cout << "ID of message: ";
		cin >> messageid;
		cout << "Priority of message: ";
		cin >> priority;
		cout << "Source Address of message: ";
		cin >> source_address;
		cout << "Destination Address of message: ";
		cin >> destination_address;
		cout << "Payload of message: ";
		cin >> payload;
		cout << "Trace of message: ";
		cin >> trace;
		cout << endl;
		file << messageid << "," << priority << "," << source_address << "," << destination_address << "," << payload << "," << trace;
		file << endl;
		file.close(); // Close the file after writing

	}

	// Function for checking priority ogf messages
	bool operator> (const Messages& other) const
	{

		return priority > other.priority;// returning highest prioriy

	}

};


class settingmessages  // on the basis of priority
{
public:

	bool operator()(const Messages& m1, const Messages& m2)
	{
		return m1.priority < m2.priority;
	}
};




class AdjMatrix
{
public:
	string** matrix; // Changed to string to handle non-numeric entries
	int numRows;
	int numCols;

	AdjMatrix() : matrix(nullptr), numRows(0), numCols(0) {}

	~AdjMatrix()
	{
		for (int i = 0; i < numRows; ++i)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	void readAndStoreFile(const string& filename)
	{
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "Unable to open file" << endl;
			return;
		}

		string line, entry;
		vector<vector<string>> tempMatrix;

		// Read and store data in a temporary matrix
		while (getline(file, line))
		{
			istringstream ss(line);
			vector<string> currentRow;
			while (getline(ss, entry, ','))
			{
				currentRow.push_back(entry);
			}
			tempMatrix.push_back(currentRow);
		}

		// Close the file
		file.close();

		// Set the matrix dimensions
		numRows = tempMatrix.size();
		numCols = tempMatrix[0].size();

		// Allocate memory for the matrix
		matrix = new string * [numRows];
		for (int i = 0; i < numRows; i++)
		{
			matrix[i] = new string[numCols];
		}

		// Convert string matrix, replacing '?' with '0' where appropriate
		for (int i = 0; i < numRows; ++i)
		{
			for (int j = 0; j < numCols; ++j)
			{
				if (tempMatrix[i][j] == "?")
				{
					matrix[i][j] = "0";
				}
				else
				{
					matrix[i][j] = tempMatrix[i][j]; // Keep the original string
				}
			}
		}
	}

	void printMatrix()
	{
		for (int i = 0; i < numRows; i++)
		{
			for (int j = 0; j < numCols; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}


};



class Routers
{
public:

	priority_queue<Messages, vector<Messages>, settingmessages> In;
	queue<Messages> Out;
	vector<pair<string, string>> rt;

	int totalentries = 0;
	int maxentries = 10;
	string array1[10];
	string array2[10];

	//Arrays for Adding and Removing Entries
	string array3[10];//destinations
	string array4[10];//routers

	//Getting the Incoming Messages on the basis of highest priority
	void IncomingQueue(const Messages& msg)
	{

		In.push(msg);

	}
	// Processing the messages and setting on the basis of priority
	void SettingMessages()
	{

		while (!In.empty())
		{

			Messages M1 = In.top();
			In.pop();
			Out.push(M1);

		}
	}


	// After setting messages on the basis of priority we send them
	void SendingMessagess()
	{
		ofstream RoutingTablefile("RoutingTable.txt", ios::app);
		while (!Out.empty())
		{

			Messages M2 = Out.front();

			Out.pop();

			cout << "\nSending message from the source : ";
			cout << M2.source_address;
			cout << " to   the destination: ";
			cout << M2.destination_address;
			cout << " with the payload: ";
			cout << M2.payload;
			cout << endl << endl;


			if (totalentries < maxentries)
			{

				array1[totalentries] = M2.source_address;

				array2[totalentries] = M2.destination_address;

				RoutingTablefile << array1[totalentries];
				RoutingTablefile << " -------> ";
				RoutingTablefile << array2[totalentries];
				RoutingTablefile << endl;

				totalentries++;

			}

		}
		RoutingTablefile.close();
	}

	// Printing routing Table after sending Messages
	void printingroutingtable()
	{
		cout << "Source:   " << "Destination";

		cout << endl;

		for (int a = 0; a < totalentries; a++)
		{

			cout << array1[a];

			cout << "		  ";

			cout << array2[a];

			cout << endl;
		}
	}
	// Function for Adding Edge in the routing 
	void addRoutingEntry()
	{

		cout << "Input the NUmber of Routes you want to Add:";

		int routes;
		cin >> routes;

		cin.ignore();

		for (int a = 0; a < routes && totalentries < maxentries; a++)
		{

			string messageid, sourceaddress, destinationaddress, payload;
			int priority;

			cout << "Input Message Details ";
			cout << endl;
			cout << "Input Id:";
			cin >> messageid;
			cout << "Input Priority:";
			cin >> priority;
			cout << "Input Source Address:";
			cin >> sourceaddress;
			cout << "Destinaton Address:";
			cin >> destinationaddress;
			cout << "Payload:";
			cin >> payload;


			// Writing the Message to the Messages.txt file

			ofstream message("Messages.txt", ios::app);

			if (message.is_open())
			{
				message << messageid << "," << priority << "," << sourceaddress << "," << destinationaddress << "," << payload << endl;

				message.close();
			}
			else
			{
				cout << "Unable to Open the fIle";
				cout << endl;
			}

			// Updating Entey to the Routing table
			for (int a = 0; a < totalentries; a++)
			{
				if (array2[a] == sourceaddress && array2[a] != destinationaddress)
				{
					array4[a] = destinationaddress;

					break;
				}
			}
			//Adding new entry to the Routing Table

			if (totalentries < maxentries && (totalentries == 0 || array3[totalentries - 1] != sourceaddress || array4[totalentries - 1] != destinationaddress))
			{
				// Add new entry if not found
				array3[totalentries] = sourceaddress;

				array4[totalentries] = destinationaddress;

				totalentries++;

				ofstream RoutingTableFile("RoutingTable.txt", ios::app);// Writing the new edgr in the Routing Table
				if (RoutingTableFile.is_open())
				{
					RoutingTableFile << sourceaddress << "------> " << destinationaddress << endl;

					RoutingTableFile.close();
				}
				else
				{
					cout << "Unable to open the File ";
					cout << endl;
				}
			}
		}
	}
	// Function for Removing Edge in the routing 






};


class Network
{
public:
	AdjMatrix AM;

	void Read_Print_RT()
	{
		AM.readAndStoreFile("network.csv");
		AM.printMatrix();
	}

	//function for making making routing table for each router 
	void RoutingTableforRouter()
	{
		ifstream file("network.csv");
		if (!file.is_open()) {
			cout << "Unable to open file network.csv";
			cout << endl;
			return;
		}

		string l;
		vector<vector<string>> NetworkMatrix;

		// reading data from the CSV file 
		while (getline(file, l))
		{
			istringstream ss(l);
			string token;
			vector<string> row;
			while (getline(ss, token, ','))
			{
				row.push_back(token);
			}
			NetworkMatrix.push_back(row);
		}

		file.close();

		// printing routing table for routers only
		for (int i = 16; i < NetworkMatrix.size(); i++)
		{
			string routerName = NetworkMatrix[i][0];

			if (routerName[0] == 'R')
			{
				// checking if the entry represents a router
				cout << "Routing Table for Router " << routerName << ":" << endl;

				for (int j = 1; j <= 20; j++)
				{
					if (NetworkMatrix[i][j] != "?")
					{
						cout << "Destination: " << NetworkMatrix[0][j] << "weight : " << NetworkMatrix[i][j] << endl;
					}
				}
				cout << endl;
			}
		}
	}


	// Function for Printing Path



	// Function for printing the path to file in comma-separated format
	void printPathToFile(const string& source, const string& destination, const string& payload)
	{
		ofstream outFile("path.txt", ios::app); // Open file in append mode
		if (outFile.is_open())
		{
			outFile << source << "," << destination << "," << payload << endl;
			outFile.close();
			cout << "Path details saved to path.txt" << endl;
		}
		else
		{
			cout << "Unable to open file path.txt" << endl;
		}

	}
	bool interruptOccurred = false;

	// Signal handler function for interrupt
	void interruptHandler(int signal)
	{
		interruptOccurred = true;
	}

	// Function to handle timer interrupts and move messages from outgoing to incoming queues
	void handleInterrupt(queue<string>& outgoingQueue, queue<string>& incomingQueue)
	{
		// Check if the outgoing queue is not empty
		if (!outgoingQueue.empty())
		{
			// Get the message from the outgoing queue
			string message = outgoingQueue.front();

			// Remove the message from the outgoing queue
			outgoingQueue.pop();

			// Move the message to the incoming queue
			incomingQueue.push(message);
		}

		// Reset flag
		interruptOccurred = false;
	}

	void MessagesToBeSend()
	{
		queue<string> outgoingQueue;
		queue<string> incomingQueue;

		for (int i = 0; i < 3; ++i) {
			string source, destination, payload;
			cout << "Enter the source address for message " << i + 1 << ": ";
			cin >> source;
			cout << "Enter the destination address for message " << i + 1 << ": ";
			cin >> destination;
			cout << "Enter the payload of message " << i + 1 << ": ";
			cin.ignore(); // Ignore any previous newline character
			getline(cin, payload);

			// Send the message by adding it to the outgoing queue
			outgoingQueue.push("Message " + to_string(i + 1) + ": From " + source + " to " + destination + " with payload: " + payload);

			// Call interrupt function to emulate network delay
			handleInterrupt(outgoingQueue, incomingQueue);

			// Simulate processing time
			cout << "Processing message " << i + 1 << "...\n";
			Sleep(6000); // Simulate processing time
		}

		// Print incoming queue contents after all messages are sent
		cout << "\nIncoming queue contents:\n";
		while (!incomingQueue.empty()) {
			cout << incomingQueue.front() << endl;
			incomingQueue.pop();
		}
	}





	// function for changing routing table
	void ChangeRoutingTable()
	{

	}


	// function for changing the edge weight
	void ChangingWeight()
	{

	}
};




int main()
{
	// Object for Message class
	Messages M;

	// object for routers
	Routers R;

	Network N;

	int choice;
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
	cout << endl;
	cout << "           NETWORK EMULATOR";
	cout << endl;
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
	cout << endl;
	cout << endl;
	do
	{
		cout << "Choose an option:";
		cout << endl;
		// Phase 01
		cout << "1. Take Input from the Terminal and Write into the File"; // done
		cout << endl;
		cout << "2. Read a Message from the file (Messages.txt)"; // done
		cout << endl;
		cout << "3. Sending Messages and Printing Routing Table "; // done
		cout << endl;
		cout << "4. Adding edge to the routing table ";
		cout << endl;
		cout << "5. Removing edge from the routing table entry";
		cout << endl;
		//Phase 02
		cout << "6. Reading the CSV File and Printing Routing Table according to the File";
		cout << endl;
		cout << "7. Routing Table for each Router ";
		cout << endl;
		cout << "8. Printing Path for message ";
		cout << endl;
		cout << "9.Message to be send ";
		cout << endl;
		cout << "10. Changing Routing Table entries ";
		cout << endl;
		cout << "11. Changing the weight of the edge in routing table ";
		cout << endl;

		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
		{
			cout << "-----------------------------------------------------------------------------------";
			cout << endl;
			cout << "Please Input Message Details from the Terminal these details get saved in the file";
			cout << endl;
			M.InputMessages();
			cout << endl;
			cout << endl;
			M.DisplayDetails();
			cout << endl;
			cout << "-----------------------------------------------------------------------------------";
			break;
		}

		case 2:
		{
			cout << "-----------------------------------------------------------------------------------";
			cout << endl;
			cout << "Reading a message from the File";
			cout << endl;

			// Pass an empty string to ReadMessages since it doesn't take any parameters
			M.ReadMessages("");
			cout << "----------------------------------";
			cout << endl;
			cout << endl;
			M.DisplayDetails();
			cout << endl;
			break;
		}


		case 3:
		{
			cout << "-----------------------------------------------------------------------------------";
			ifstream file("Messages.txt"); // Open the file

			if (!file.is_open())
			{
				cout << "Unable to open file Messages.txt";
				cout << endl;
				break;
			}

			string l;
			while (getline(file, l))
			{
				stringstream cin(l);

				string messageid;
				int priority;
				string source_address;
				string destination_address;
				string payload;
				string trace;


				getline(cin, messageid, ',');

				cin >> priority;
				cin.ignore();

				getline(cin, source_address, ',');
				getline(cin, destination_address, ',');
				getline(cin, payload, ',');
				getline(cin, trace);


				Messages M3(messageid, priority, source_address, destination_address, payload, trace);

				R.IncomingQueue(M3);
				R.SettingMessages();
				R.SendingMessagess();

				cout << "Printing Routing Table:";
				cout << endl << endl;
				R.printingroutingtable();

			}
			file.close();
			cout << "-----------------------------------------------------------------------------------";

			break;

		}

		case 4: // add edge
		{
			cout << "-----------------------------------------------------------------------------------";
			cout << endl;
			R.addRoutingEntry();

			cout << "----------------------------------";
			cout << endl;
			cout << endl;
			break;
		}

		case 5:
		{
			// remove edge
			cout << "-----------------------------------------------------------------------------------";
			cout << endl;
			//R.RemoveRoutingEntry();

			cout << "----------------------------------";
			cout << endl;
			cout << endl;
			break;

		}

		case 6:
		{

			cout << "-----------------------------------------------------------------------------------";
			cout << "Reading the CSV File and Printing the initial Routing Table from csv file ";
			cout << endl;

			N.Read_Print_RT();
			cout << endl;

			cout << "-----------------------------------------------------------------------------------";
			break;
		}

		case 7:
		{
			cout << "-----------------------------------------------------------------------------------";

			cout << "Routing Table for each Router ";
			cout << endl;

			N.RoutingTableforRouter();

			cout << endl;

			cout << "-----------------------------------------------------------------------------------";
			break;
		}

		case 8:
		{
			cout << "-----------------------------------------------------------------------------------" << endl;
			cout << "Printing Path for Message";
			cout << endl;

			cout << "-----------------------------------------------------------------------------------" << endl;
			break;
		}

		case 9:
		{
			cout << "-----------------------------------------------------------------------------------";

			cout << "Message to be send ";
			cout << endl;

			N.MessagesToBeSend();
			cout << endl;

			cout << "-----------------------------------------------------------------------------------";
			break;

		}

		case 10:
		{
			cout << "-----------------------------------------------------------------------------------";
			cout << "Changing Routing Table entries ";
			cout << endl;
			N.ChangeRoutingTable();

			cout << "-----------------------------------------------------------------------------------";
			break;

		}

		case 11:
		{
			cout << "-----------------------------------------------------------------------------------";
			cout << "Changing the weight of the edge in routing table ";
			cout << endl;
			N.ChangingWeight();
			cout << "-----------------------------------------------------------------------------------";
			break;
		}




		default:
			cout << "Invalid choice. Please try again.";
			cout << endl;
			break;
		}
	} while (choice != 9);

	return 0;
}