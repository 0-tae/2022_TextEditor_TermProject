#pragma once

enum {
	ERROR_NONE = 0, ERROR_QUIT=1,
	ERROR_101 = 101, ERROR_102 = 102, ERROR_103 = 103,
	ERROR_201 = 201,
	ERROR_301 = 301, ERROR_302 = 302, ERROR_303 = 303,
	ERROR_UNDEFINED=-1};

/*
 -> 1xx error = 잘못된 입력

101 : 입력 string의 길이
102 : 잘못된 입력
103 : 명령어는 존재하나 그에 맞지않는 인자의 입력

-> 2xx error = 잘못된 참조
201 : 입력이 현재 index 범위를 벗어남

-> 3xx error = 동작상 오류 (결과 값 찾지 못함, 페이지 이동 제한)
301 : 첫 번째 페이지에서 p 명령어 시도
302 : 마지막 페이지에서 n 명령어 시도
303 : 원하는 결과값을 찾지 못했을 경우

-> UNDEFINED error = 알수없는 오류
*/
