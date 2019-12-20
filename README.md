# <Aduino Uno를 활용한 기억력 게임 시스템>

__김연준, 이세민, 한승우__

### 0. 개요
------------------------------
1. 아두이노로 재미있는 게임을 구현하기 위하여 선정

2. 다양한 센서를 활용하여 기억력을 기르기 위한 게임 제작

<img src="/images/슬라이드4.pNG" width="50%"><img src="/images/슬라이드5.PNG" width="50%">

### 1. 시스템 고려요소
------------------------------
- 인터럽트 처리: 7-세그먼트에 표시된 타이머 0이 되면 게임을 종료 시키는 인터럽트 발생(타이머 인터럽트)

- 동시 진행: 타이머 작동 하면서 문제 맞추는 과정(MsTimer2 라이브러리 사용)

- 창의적 요소: 고려하여 기억력게임과 아두이노의 장애물 감지 센서 결합

- 핀 부족: ‘74HC595’를 활용하여 핀 개수 줄임

 오류 발생 문제: 조건문(if) 활용한 엄밀한 예외 처리

### 2. 참고
------------------------------
 * Aduino 공식 사이트
 
### 3. Detail
------------------------------
 * Tool: Arduino IDE
 * 언어: C++
 

##### Copyright 2019. 김연준, 이세민, 한승우 inc. all rights reserved
