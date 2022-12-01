# StreetDataReading

A simple dictionary based on a linked list to store information from a dataset about the City of Melbourne. A user will be able to search this dictionary to retrieve information about footpaths in Melbourne using attributes in the dataset (keys). 

The implementation will build the dictionary by reading the data from a file and inserting each footpath record as a node in a linked list. This will also implement a method to search for a key in the list, outputting any records that match the key. Note that keys are not guaranteed to be unique!


dict1:

- Read the data from the data file specified in the second command line argument. The data from the CSV should be stored in a linked list of pointers to structs for the data. Datatypes for each field should be consistent with those in the Dataset slide. Each record (row) should be stored in a separate node.

- Accept addresses from stdin, search the list for all matching records and print them to the output file. You may assume that all queries will be terminated by a new line to allow for the querying of footpaths without an address. If no matches for the query are found, your program should output NOTFOUND.

- In addition to outputting the record(s) to the output file, the number of records found should be output to stdout.
