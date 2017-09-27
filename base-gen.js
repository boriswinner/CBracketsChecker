"use strict"
function randomInteger(min, max) {
    var rand = min + Math.random() * (max + 1 - min);
    rand = Math.floor(rand);
    return rand;
  }


var fs = require('fs');
var output = "cr.sql";
var res = "CREATE DATABASE 'test.fdb' USER 'sysdba' PASSWORD 'masterkey';\n";
res += "CREATE TABLE students (id INTEGER, name VARCHAR (100), birthday DATE, group_id INTEGER);\n";
var mnames = ["Сергей","Эдуард","Адольф","Саша","Валентин","Степан","Бронислав","Ян"];
var fnames = ["Дарья","Марья","Надежда","Рита","Станислава","Валентина","Светлана"];
var msnames = ["Андреевич","Степанович"];
var fsnames = ["Борисовна","Алексеевна"];
var famnames = ["Приходько","Бутко","Тимофеенко","Зинькович","Дуб","Полено","Зудь","Дудь"];
var maxgroup = 10;
var maxstudies = 15;
var maxstudents = 100;
var students_group_ids = [];

for (var i = 0; i < maxstudents; ++i){
	var gender = randomInteger(0,1);
	var group_id = randomInteger(0,maxgroup);
	students_group_ids.push(group_id);
	
	if (gender){
		res += "INSERT INTO students VALUES (" + i + ", '" + mnames[randomInteger(0,mnames.length-1)] + " " + msnames[randomInteger(0,msnames.length-1)] + ' ' + famnames[randomInteger(0,famnames.length-1)] + "', '" + randomInteger(1900,2000) + '-' + randomInteger(1,12) + '-' + randomInteger(1,27) + "', " + group_id + ');\n';		
	} else {
		res += "INSERT INTO students VALUES (" + i + ", '" + fnames[randomInteger(0,fnames.length-1)] + " " + fsnames[randomInteger(0,fsnames.length-1)] + ' ' + famnames[randomInteger(0,famnames.length-1)] + "', '" + randomInteger(1900,2000) + '-' + randomInteger(1,12) + '-' + randomInteger(1,27) + "', " + group_id + ');\n';
	}
}

var groupprefixes = ["Прикладная","Фундаментальная","Теоритическая","Информационная","Ядерная"];
var groups = ["Информатика","Математика","Физика","Лингвистика","Механика","Химия"];

res += "CREATE TABLE groups (id INTEGER, name VARCHAR (100));\n";
for (var i = 0; i < maxgroup; ++i){
	res += "INSERT INTO groups VALUES (" + i + ", '" + groupprefixes[randomInteger(0,groupprefixes.length-1)] + ' ' + groups[randomInteger(0,groups.length-1)] + "');\n";
}


var studies = ["Архитектура компьютера","ПЭВМ","Матан","Алгебра","Основы Православной Культуры","Урок Толерантности","Физическая Подготовка для Умственно Отсталых","ОБЖ"];
var studies_group_ids = [];

res += "CREATE TABLE studies (id INTEGER, name VARCHAR (100), groupid INTEGER);\n";
for (var i = 0; i < maxstudies; ++i){
	var study_id = randomInteger(0,maxstudies);
	studies_group_ids.push(study_id);
	res += "INSERT INTO studies VALUES (" + i + ", '" + studies[randomInteger(0,studies.length-1)] + "', " + study_id +  ");\n";
}

res += "CREATE TABLE scores (student_id INTEGER, study_id INTEGER, score INTEGER);\n";
for (var i in students_group_ids){
	for (var j in studies_group_ids){
		if (students_group_ids[i] === studies_group_ids[j]){
			res += "INSERT INTO scores VALUES (" + i + ", " + j + ", " + randomInteger(2,5) + ');\n';
		}
	}
}


fs.writeFileSync(output, res);