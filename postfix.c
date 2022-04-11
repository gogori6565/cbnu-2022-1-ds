#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE]; //infix 표현
char postfixExp[MAX_EXPRESSION_SIZE]; //postfix 표현
char postfixStack[MAX_STACK_SIZE]; //스택 배열
int evalStack[MAX_STACK_SIZE]; //eval 스택 배열

int postfixStackTop = -1; //스택 배열 top 초기값 = -1
int evalStackTop = -1; //eval 스택 배열 top 초기값 = -1

int evalResult = 0; //결과값 저장할 변수

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command; //메뉴 입력 변수

   printf("[----- [이주현]  [2021041075] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default: //옳지 않은 값이 입력되었을 경우 경고 메세지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q가 들어올 경우 반복문 종료

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; //스택의 top을 1 증가시키고 그 위치에 x값 삽입
}

//pop : 스택에서 빼오기
char postfixPop()
{
	char x;
    if(postfixStackTop == -1) //스택의 top이 -1인 경우
        return '\0'; //\0값 반환
    else { //아닌경우
    	x = postfixStack[postfixStackTop--]; //스택의 top값을 x에 저장한 후에 top 값 -1
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; //eval 스택의 top을 먼저 1 증가시키고 그 top의 위치의 스택에 x 값 삽입
}

//eval 스택 값 pop하기(빼기)
int evalPop()
{
    if(evalStackTop == -1) //eval 스택의 top이 -1인 경우
        return -1; //함수 끝
    else //아닌 경우
        return evalStack[evalStackTop--]; //eval 스택의 top 위치의 값 반환한 후에 top -1
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); //사용자로부터 infix 표기식을 입력받음 -> 그걸 infixExp에 저장
}

//수식 스트링으로부터 토큰 얻기
precedence getToken(char symbol)
{
    //symbol은 문자 표현이며, token은 그것의 열거된 값으로 표현되고 명칭으로 반환한다
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand; //에러 검사 하지 않고 기본 값은 피연산자
	}
}

precedence getPriority(char x)
{
	return getToken(x); //수식 스트링으로부터 토큰 얻기 위한 함수 호출 후 값 반환
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0') //postfixExp가 \0인 경우 (빈 공간)
		strncpy(postfixExp, c, 1); //c 문자를 postfixExp로 복사하는데 1만큼만 복사
	else
		strncat(postfixExp, c, 1); //c 문자 1개를 postfixExp 뒤쪽에 이어 붙이기
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0') //exp의 값이 \0이 아닐 때까지 반복
	{
        //포인터 exp가 가리키는 문자가 피연산자인 경우
		if(getPriority(*exp) == operand) 
		{
			x = *exp;    //포인터 exp가 가리키는 값을 x에 저장
        	charCat(&x); //charCat함수에 x의 주소 전달 (postixExp에 저장할 것임)
		}
        //포인터 exp가 가리키는 문자가 '('인 경우
        else if(getPriority(*exp) == lparen) {
        	postfixPush(*exp); //스택에 삽입
        }
        //포인터 exp가 가리키는 문자가 ')'인 경우
        else if(getPriority(*exp) == rparen)
        {
            //오른쪽 괄호가 나오면 왼쪽 괄호가 나올 때까지 pop
        	while((x = postfixPop()) != '(') {
        		charCat(&x); //postfixExp에 저장
        	}
        }
        //포인터 exp가 가리키는 문자가 연산자인 경우
        else
        {
            //스택의 top에 있는 연산자가 exp가 가리키는 연산자보다 우선순위가 높거나 같은 경우 반복
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
            {
            	x = postfixPop(); //현재 스택의 top값을 pop해서 x에 저장
            	charCat(&x); //x값을 postfixExp에 추가
            }
			//exp가 가리키는 연산자가 우선순위가 높은 경우
            postfixPush(*exp); //exp가 가리키는 연산자 스택에 삽입
        }
        exp++; //exp +1 증가
	}

    //스택의 top이 -1이 아닐 때까지 반복 = 최종 값 가져오기
    while(postfixStackTop != -1)
    {
    	x = postfixPop(); //스택에서 top부터 빼오기
    	charCat(&x); //postfixExp에 추가
    }

}

//infixExp, postfixExp, evalResult, postfixStack 출력
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);     //infixExp 출력
	printf("postExp =  %s\n", postfixExp);    //postfixExp 출력
	printf("eval result = %d\n", evalResult); //evalResult 출력

    //postfixStack 출력
	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

//infixExp, postfixExp, evalResult, postfixStack 초기화
void reset()
{
	infixExp[0] = '\0';   //infixExp 초기화
	postfixExp[0] = '\0'; //postfixExp 초기화

    //postfixStack 초기화
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1; //스택 top -1
	evalStackTop = -1;    //eval 스택 top -1
	evalResult = 0;       //evalResult 0
}

//후위 표기식 연산값
void evaluation()
{
	int opr1, opr2, i;

	int length = strlen(postfixExp); //postfixExp의 길이 length에 저장
	char symbol;
	evalStackTop = -1;

    //0~length-1까지 반복
	for(i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
        //symbol이 가리키는 값이 피연산자 인 경우
		if(getToken(symbol) == operand) {
			evalPush(symbol - '0');
            //symbol은 char 자료형이므로 0의 아스키 코드 10진수 값 48을 빼면 숫자를 얻을 수 있음 - 스택 삽입
		}
		else {
            //두 피연산자를 삭제하여 연산을 수행한 후, 그 결과를 스택에 삽입

            //스택에서 값 두 개 빼옴
			opr2 = evalPop();
			opr1 = evalPop();

			switch(getToken(symbol)) {
			case plus: evalPush(opr1 + opr2); break;   //덧셈 연산 -> 스텍에 삽입
			case minus: evalPush(opr1 - opr2); break;  //뺄셈 연산 -> 스텍에 삽입
			case times: evalPush(opr1 * opr2); break;  //곱셈 연산 -> 스텍에 삽입
			case divide: evalPush(opr1 / opr2); break; //나눗셈 연산 -> 스텍에 삽입
			default: break;
			}
		}
	}
	evalResult = evalPop(); //결과 반환
}