# StreetDataReading

A simple dictionary based on a linked list to store information from a dataset about the City of Melbourne. A user will be able to search this dictionary to retrieve information about footpaths in Melbourne using attributes in the dataset (keys). 

The implementation will build the dictionary by reading the data from a file and inserting each footpath record as a node in a linked list. This will also implement a method to search for a key in the list, outputting any records that match the key. Note that keys are not guaranteed to be unique!


dict1:

- Read the data from the data file specified in the second command line argument. The data from the CSV should be stored in a linked list of pointers to structs for the data. Datatypes for each field should be consistent with those in the Dataset slide. Each record (row) should be stored in a separate node.

- Accept addresses from stdin, search the list for all matching records and print them to the output file. You may assume that all queries will be terminated by a new line to allow for the querying of footpaths without an address. If no matches for the query are found, your program should output NOTFOUND.

- In addition to outputting the record(s) to the output file, the number of records found should be output to stdout.

dict2:

- Construct a sorted array which contains pointers to each node in the dataset. This should be sorted on the grade1in attribute, which will be the 6th index (0-based).

- Accept double type values from stdin, search the index for the closest record to that value and print it to the output file. The closest point is defined by the absolute difference between the search value and the dataset value.

- In addition to outputting the record(s) to the output file, the grade1in value of the record found should be output to stdout.

dict3:

- Construct a quadtree from the stored data.

- Interpret and store the fourth, fifth, sixth and seventh arguments as long double values. The strtold  function should be used to achieve this.

- Accept co-ordinate pairs from stdin, search the constructed quadtree for the point region containing the co-ordinate pair and print all matching records to the output file.

- In addition to outputting the record(s) to the output file, the list of quadrant directions followed from the root until the correct point region is found should be output to stdout.

- Insert each footpath's (start_lon, start_lat) and (end_lon, end_lat) pairs into the quadtree, allowing the footpath to be found from its start or end point.

- Where multiple footpaths are present in the found point region, footpaths should be printed in order of footpath_id.

dict4:

- Accept sets of pairs of co-ordinate long double type values from stdin, and efficiently use the quadtree to find all footpaths which are within the bounds of the query.

- Output to stdout should include all directions searched in order, with each branch potentially containing points within the query bounds fully explored before proceeding to the next possible branch. Where multiple directions are possible, quadrants must be searched in the order SW , NW , NE, SE . Each direction must be separated by a space.

- Where multiple footpaths are returned by the range query, these should be sorted by footpath_id. Output each footpath only once for each query, even if both its "start" and "end" points both occur in the searched region.
