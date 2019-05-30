# MineSweeper
2019-1 오픈소스SW개론(001) 과제 3~5 Project MineSweeper


# **1. 프로젝트 이름**

Minesweeper


# **2. 프로젝트 소개**

본 프로젝트는 오픈소스를 수강하는 학생들로 구성된 팀 프로젝트입니다. 

지뢰찾기 게임을 콘솔 창에서 즐길수 있도록 개발하였습니다.  

>지뢰찾기는 1960년대와 1970년대 초기 메인프레임 컴퓨터 게임에서 시작한 게임으로, 
격자 형태로 이루어진 “지뢰밭”에서 지뢰가 없는 칸을 전부 열면 이기는 게임이다. 지뢰가 있는 칸을 열 경우 게임이 종료되고, 
지뢰가 없는 칸을 누를 경우 열린 칸에 맞닿은 둘레에 숨겨진 지뢰의 총 개수가 열린 칸 내부에 표시된다.


# **3. 개발 환경**


운영체제: Windows 10

개발 툴: Visual Studio

개발 언어: C 



# **4. 라이센스**


Apache License Version 2.0


# **5. 플레이 방법**

<img src="https://user-images.githubusercontent.com/48747805/58545622-991e6500-823e-11e9-9820-6dd5fd6fb777.png" width="50%"></img>

(1) 인트로 화면에서 5~16 사이의 게임판의 행렬 크기를 입력한다.

<img src="https://user-images.githubusercontent.com/48747805/58575411-f2a58480-827c-11e9-99d3-4426e8cb5e6b.png" width="50%"></img>

(2) 블록의 행렬을 입력한다

<img src="https://user-images.githubusercontent.com/48747805/58575665-89724100-827d-11e9-9524-4ee7f3a4ffa6.png" width="50%"></img>
<img src="https://user-images.githubusercontent.com/48747805/58575604-5e87ed00-827d-11e9-9e4a-4bd0708a45e0.PNG" width="50%"></img>

(3) 블록을 열고 싶으면 1을, 깃발로 표시·깃발을 해지하는 경우 2를 입력한다. 

<img src="https://user-images.githubusercontent.com/48747805/58575801-d1916380-827d-11e9-9d3a-c59d4e72c67a.PNG" width="50%"></img>

(4) 지뢰가 아니라면 주변 8칸에 있는 지뢰의 수가 표시된다

<img src="https://user-images.githubusercontent.com/48747805/58575805-d2c29080-827d-11e9-8883-0dc94847977d.png" width="50%"></img>

(5) 위의 과정을 반복하여 지뢰를 제외한 모든 블록을 열면 최종적으로 게임에서 승리한다.


# **6. 버그 사항**


~~행렬을 입력 받을 때 숫자가 아닌 문자를 입력할 경우 무한 루프되는 버그 발생~~ (19.05.30 해결)









