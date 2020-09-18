#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>
using namespace std;
struct Session;
struct Course;
struct CourseGrade;
typedef vector<Course> CourseTable;
typedef vector<Session> CourseTime;
typedef vector<CourseGrade> GradeTable;
typedef vector<int> PreIds ;
float assign_time(string connected_time);
CourseTime assign_course_time(string unseparated_time);
PreIds assign_prereq(string connected_pre);
Course assign_course(string line);
CourseTable read_course_info(string file_path);
CourseGrade assign_grade(string course_grade);
GradeTable read_grades(string file_path);
bool is_takable(Course this_course,CourseTable courses_taken);
CourseTable find_takable_courses(CourseTable all_courses ,GradeTable grades_taken);
bool compare_string(string a, string b);
float calc_average(GradeTable given_table , CourseTable all_courses);
bool compare_units_names(Course a , Course b);
int sum_of_units(CourseTable takable_courses);
int min_un(int units_sum);
int max_un(float average);
bool have_contrast(Course first , Course second);
void generate_output(CourseTable ordered_courses ,float average , int units_sum);

struct Course
{
  int id;
  string name;
  int units;
  CourseTime schedule;
  PreIds prerequisites;
};
struct Session
{
  string day;
  float start;
  float end;
};
struct CourseGrade
{
  int id;
  float grade;
};
int main(int argc, char* argv[])
{
  CourseTable our_courses ;
  int our_courses_size = read_course_info(argv[1]).size();
  for(int k = 0 ; k < our_courses_size ; k++)
    our_courses.push_back(read_course_info(argv[1])[k]);

  GradeTable our_grades;
  int our_grades_size = read_grades(argv[2]).size();
  for(int k = 0 ; k < our_grades_size ; k++)
    our_grades.push_back(read_grades(argv[2])[k]);

  float GPA = calc_average(our_grades , our_courses) ;

  CourseTable takables ;
  int takables_size = find_takable_courses(our_courses , our_grades).size();
  for(int k = 0 ; k < takables_size ; k++)
    takables.push_back(find_takable_courses(our_courses , our_grades)[k]);

  sort(takables.begin(), takables.end() , compare_units_names);

  int units = sum_of_units(takables);
  generate_output(takables ,GPA , units) ;


}
float assign_time(string connected_time)
{
  stringstream separated_time(connected_time);
  int track = 0 ;
  float hour ,minutes ;
  while(separated_time.good())
  {
    if(track == 0)
    {
      string temp;
      getline(separated_time, temp , ':');
      hour = stof(temp);
    }
    else if(track == 1)
    {
      string temp ;
      getline(separated_time, temp , ':');
      minutes = stof(temp);
      float total_time = hour + (minutes/60);
      return total_time ;
    }
    track++ ;
  }

}

CourseTime assign_course_time(string unseparated_time)
{
  CourseTime schedule;
  stringstream class_schedule(unseparated_time);
  while(class_schedule.good())
  {
    string schedule_sessions;
    getline(class_schedule, schedule_sessions , '/');
    stringstream class_session_parts(schedule_sessions);
    int parts_track = 0 ;
    Session session ;
    while(class_session_parts.good())
    {
      string session_part;
      getline(class_session_parts, session_part , '-');
      if(parts_track == 0)
        session.day = session_part;
      else if(parts_track == 1)
        session.start = assign_time(session_part);
      else if(parts_track == 2)
        session.end = assign_time(session_part);
      parts_track++;
    }
    schedule.push_back(session);
  }
  return schedule ;
}
PreIds assign_prereq(string connected_pre)
{
  stringstream separated_preqs(connected_pre);
  PreIds preqs ;
  while(separated_preqs.good())
  {
    string temp;
    getline(separated_preqs, temp , ':');
    preqs.push_back(stoi(temp));
  }
  return preqs;
}
Course assign_course(string line)
{
  stringstream parts(line);
  Course line_course;
  int count = 0 ; //keeps track of where we are in the course identities
  while(parts.good())
   {
      string substring;
      getline(parts, substring, ','); //separating the values in each file
      if(count == 0)
        line_course.id = stoi(substring);
      else if(count == 1)
        line_course.name = substring;
      else if(count == 2)
        line_course.units = stoi(substring);
      else if(count == 3)
        line_course.schedule = assign_course_time(substring);
      else if(count == 4)
        line_course.prerequisites = assign_prereq(substring) ;
      count++;
  }
  return line_course;
}
CourseTable read_course_info(string file_path)
{
  ifstream infile;
  infile.open(file_path);
  string new_line;
  CourseTable new_table;
  Course each_course ;
  int line_num = 0 ; //the first line
  while (getline(infile, new_line))
  {
    if(line_num == 0)
    {
      line_num++ ;
      continue ;
    }

    each_course = assign_course(new_line);
    new_table.push_back(each_course);
  }
  return new_table;
}

CourseGrade assign_grade(string course_grade)
{
  stringstream parts(course_grade);
  CourseGrade this_grade;
  int count = 0 ; //keeps track of where we are in the grade identities
  while(parts.good())
  {
    string substring;
    getline(parts, substring, ',');
    if(count == 0)
      this_grade.id = stoi(substring);
    else if(count == 1)
      this_grade.grade = stof(substring);
    count++;
  }
  return this_grade;
}

GradeTable read_grades(string file_path)
{
  ifstream infile;
  infile.open(file_path);
  string new_line;
  GradeTable this_table;
  CourseGrade each_grade;
  int line_num = 0 ; //the first line
  while (getline(infile, new_line))
  {
    if(line_num == 0)
    {
      line_num++ ;
      continue ;
    }

    each_grade = assign_grade(new_line);
    this_table.push_back(each_grade);
  }
  return this_table;

}

bool is_takable(Course this_course,GradeTable grades_taken)
{

  const int passing_grade = 10 ;
  int preqs_size = this_course.prerequisites.size() ;
  int num_of_taken = grades_taken.size() ;
  int total_taken = 0 ;
  for(int i = 0 ; i < preqs_size ; i++)
  {
    for(int j = 0 ; j < num_of_taken ; j++)
    {
      if( (this_course.id == grades_taken[j].id)  && (grades_taken[j].grade >= passing_grade) ) //taken before
        return false;
      else if( this_course.prerequisites[i] == grades_taken[j].id  && grades_taken[j].grade >= passing_grade )
      {
        total_taken += 1 ;
        continue;
      }
    }
  if(total_taken == preqs_size)
    return true ;
  else if(this_course.prerequisites.size() == 1 && this_course.prerequisites[0] == 0)
        return true ;
  else
    return false;
  }
}
CourseTable find_takable_courses(CourseTable all_courses ,GradeTable grades_taken)
{
  int num_all_courses = all_courses.size();
  CourseTable takable_courses;
  for(int k = 0 ; k < num_all_courses ; k++)
  {
    if(is_takable(all_courses[k] , grades_taken))
      takable_courses.push_back(all_courses[k]);
  }
  return takable_courses;
}

bool compare_string(string a, string b)
{
    return a < b;
}


int sum_of_units(CourseTable takable_courses)
{
  int table_size = takable_courses.size() ;
  int sum = 0 ;
  for(int i = 0 ; i < table_size ; i++)
    sum += takable_courses[i].units ;
}

float calc_average(GradeTable given_table , CourseTable all_courses)
{
  int given_size = given_table.size() ;
  int all_size = all_courses.size();
  int units_size = 0 ;
  float sum = 0 ;
  for(int i ; i < given_size ; i++)
  {
    for(int j = 0 ; j < all_size ; j++)
    {
      if(given_table[i].id == all_courses[j].id)
      {
        sum += all_courses[j].units * given_table[i].grade ;
        units_size += all_courses[j].units ;
        break ;
      }
    }
  }
  return sum / float(units_size);

}

bool compare_units_names(Course a , Course b)
{
  if(a.units == b.units)
    return a.name < b.name ;
  else
    return a.units > b.units ;
}

int min_un(int units_sum)
{
  const int min = 12 ;
  if(units_sum < min)
    return units_sum ;
  else
    return min ;
}

int max_un(float average)
{
  const int normal_max = 20 ;
  const int extreme_max = 24 ;
  if(average >= 17)
    return extreme_max ;
  else
    return normal_max;
}
bool have_contrast(Course first , Course second)
{
  int first_schedule_size = first.schedule.size();
  int second_schedule_size = second.schedule.size();
  for(int i = 0 ; i < first_schedule_size ; i++)
  {
    for(int j = 0 ; j < second_schedule_size ; j++)
    {
      if(first.schedule[i].day == second.schedule[j].day)
      {
        if(!((first.schedule[i].end <= second.schedule[j].start) || (second.schedule[j].end <= first.schedule[i].start)))
          return true ;
      }
    }
  }
  return false ;
}
void generate_output(CourseTable ordered_courses ,float average , int units_sum)
{

  int table_size = ordered_courses.size() ;
  int min_units = min_un(units_sum);
  int max_units = max_un(average) ;
  int units = 0 ;
  int not_compatible ;
  CourseTable final_table ;
  for(int c = 0 ; c < table_size ; c++)
  {
    units += ordered_courses[c].units ;
    if(units > max_units)
    {
      units -= ordered_courses[c].units ;
      continue ;
    }
    not_compatible = 0 ;
    for(int pre = 0 ; pre < final_table.size() ; pre++)
    {
    if(have_contrast(ordered_courses[c],final_table[pre]))
    {
      units -= ordered_courses[c].units ;
      not_compatible +=1 ;
      break;
    }
    }
    if(not_compatible != 0 )
      continue ;
    else
      final_table.push_back(ordered_courses[c]);
  }
  vector<string> name_table ;
  int total_size = final_table.size();
  for(int i = 0 ; i < total_size ; i++)
  {
    name_table.push_back(final_table[i].name);
  }
  sort(name_table.begin(), name_table.end() , compare_string);
  for(int i = 0 ; i < total_size ; i++)
  {
    for(int j = 0 ; j < total_size ; j++)
    {
      if(name_table[i] == final_table[j].name)
      {
        cout << final_table[j].id << endl ;
        break ;
      }
    }
  }
}
