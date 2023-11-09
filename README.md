# Library-System-With-Files
# Introduction
This simple library catalog system allows users to manage and search for information about authors and books. The system is designed with the following features and functionalities:

# Data Storage
The system can store information about authors and books. Data is saved in the format of delimited fields and length indicator records. Data Records Specifications Authors Data File

Author ID [15] (Primary Key) Author Name [30] Address [30] Books Data File

ISBN [15] (Primary Key) Book Title [30] Author ID [15] (Secondary Key) Indexes

# The system maintains the following indexes:
Primary index using Author ID (for Authors data file). Primary index using ISBN (for Books data file). Secondary index using Author ID (for the Books data file). Secondary index using Author Name (for the Authors data file). Operations The system supports various operations for administrators and users:

# Administrators:
Add New Author Add New Book Update Author Name (Author ID) Update Book Title (ISBN) Delete Book (ISBN) Delete Author (Author ID)

# Users:
Print Author (Author ID) Print Book (ISBN) Write Query Record Management When adding a record, the system checks the AVAIL LIST for available space and makes appropriate changes. If a record already exists, it will not be written to the file. When deleting a record, a marker (*) is placed on the file, and appropriate changes are made to the AVAIL LIST. Search Operations Search operations utilize indexes (primary or secondary). All indexes are sorted in ascending order. Binary search is used for searching in indexes. Secondary indexes are implemented using the linked list technique, bound to the primary index.

# User Queries:
Users can write queries with specific keywords. Examples of user queries include:

Select all from Authors where Author ID='xxx'; (uses primary index) Select all from Books where Author ID='xxx'; (uses secondary index) Select Author Name from Authors where Author ID='xxx'; (uses secondary index) How to Use Run the system and choose the desired operation from the welcome screen. Follow the prompts and provide the necessary information for each operation. Important Notes All add and delete operations will affect the indexes. Updates are limited to non-key fields and will not exceed the allocated size. This library catalog system provides a simple yet effective way to manage and search for author and book information in a structured and efficient manner.
