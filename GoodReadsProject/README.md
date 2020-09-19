Goodreads is an American social cataloging website that allows individuals to search its database of books, annotations, quotes, and reviews. 
Users can sign up and register books to generate library catalogs and reading lists.[based on Wikipedia] \
GoodReads is an object oriented program divided into different classes and files to analyse the data it is given from the goodreads website.The input is given to the
program in the commandline in the form "\Goodreads.out Assets", to keep the privacy of the users who have commented in the goodreads website we have used the class 
students' names instead of them.
After executing the program as above, it is prepared for the commands below: \
show_author_info <author_id> \

show_sorted_shelf <user_id> <shelf_type> <genre> \
// <shelf_type> ∈ {read, want_to_read, currently_reading} 
// At first the books with the given genre are sorted alphabetically and then the rest of the books are sorted based on their title. 

‫‪credit‬‬ ‫>‪<user_id>\
//printing the user's credit 
//user_credit = (1/2) * (number_of_users_reviews_likes/number_of_likes +number_of_user_reviews/number_of_reviews) 

‫‪best_book‬‬ \
//the book with the highest average score 

best_reviewer \
//the reviewer with the highest number of review likes 

recommend_first_approach <user_id> \
//the recommendation is based on the sume of two criteria : score = rating + favorite_genres \
//rating = (for each review in reviews of book sum(review_rating * review_user_credit)/number_of _reviews_of _book \
//favorite_genres = 5 , if book and user favorites have genres in common \
//favorite_genres = 0 , otherwise 

For more examples I have attached the "Description.pdf" file in Persian and "Samples" which were provided in the course. 
