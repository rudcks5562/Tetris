## c++ 로 콘솔 테트리스 개발하기 프로젝트

- 노션 링크 : https://polite-boater-51a.notion.site/002958bc670f4bc7898bd50a18fd4f29?pvs=4
- 프로젝트 이름 :콘솔창 테트리스 프로젝트.

- 개발 목적 : 게임 개발 역량 및 c++ 역량 향상을 위한 프로젝트.

- 개발 언어 : c++/c 

- 개발 환경 : vs2019 및 <추가 예정.>

- 목표 : 최적화된 게임 구성과 진행 구현. 



- 버전 : 0.1

- 개발자 : 임경찬.


- 0325 현황.
- ![tetris_0325_A](https://github.com/rudcks5562/Tetris/assets/72645618/8cfe5f75-35ce-4a02-977b-a41a3de6f5f7)

---
-0328 업데이트
  ![설계_초안_tet](https://github.com/rudcks5562/Tetris/assets/72645618/b30f253c-5da3-4ac2-bf5e-f2109d9b1a4d)
  
  설계대로 클래스 구조 변경 및 블록 7개 원형(ㅡ,ㅁ,ㅗ,번개,역번개,왼총(ㄱ),오른총) 추가됨
- 0331 업데이트
- ![IMG_7937](https://github.com/rudcks5562/Tetris/assets/72645618/fa69f83e-1be6-4bbe-bfd9-04b998760c19)
종이로 플로우를 대략적으로 그려봄.
제일 중요한 gamemanager의 플로우를 보면 keymanager의 입력 듣기를 실행하는 와중에 gamemanager 내부에서 쉐도잉과 블록의 회전, 충돌, 점수환산등의 처리를 마치고 이것이 규칙에 어긋나지 않으면 csm에서 콘솔에 그림을 그려주는 과정을 대략적으로 서술하였음.
이제 남은건 구현.
- 0418 업데이트
 테스트 환경 구축 및 함수 추상적 설계 완료 , 키보드 방향키 플레이 중 입력되는지 테스트 체크 완료 
- 0508 업데이트
  블록 회전과 이동 그리고 스폰 구현 및 테스트 완료, 이후 쉐도잉과 배열맵과의 연동 처리 그리고 충돌처리 구현 예정. 
- 0511 업데이트
   블록회전과 블록이동이 겉 테두리를 벗어나지 못하게 하는 것 구현 + 게임 매니저의 배열에 의해 cvm이 그림을 그리도록 작동과정 수정
- 0517 업데이트
  블록의 쌓임과 한 라인을 채우는 경우 모두 소멸하는 기능 그리고 남은 블록들은 압축되어 떨어지는 기능 구현(큐를 사용해 bottom up으로 압축함)
  
- 0519 업데이트
  기본적인 테트리스 구현완료:(쉐도잉 제외 곧 구현 예정) + embold라는 코드분석 툴을 사용해 코드 리뷰중
- 0524 업데이트
  space로 바로 떨어지게 하는 기능 구현,쉐도잉 구현(내려갈 최종 목표점 음영으로 보이게 하는 기능) + binary search로 쉐도잉 최적위치 탐색하는 최적화 구현.(UI구현과 버그체크만 남았다!)
- 0525 코드리뷰 결과 요약. (스위치문 DEFAULT 걸기.사용하지 않는 변수 주석처리 해놓기(곧 작업할 장소이더라도.) , 대입연산자는 *this를 반환하도록 , static활용해서 정적 선언.+ 배열 c++문법으로?
- 0526 코드리뷰 반영하여 매크로 상수를 const로 전부 변경하였음 + 대입연산자 오버로딩도 return값 조정, 스위치문 default 설정. + 현재 블록배열 로테이션중 3번각도에서 1좌표에 닿지 않는 버그 발견..
<게임 플레이 화면(UI 미구현)>
- 0529 26일날 버그 리미트 함수 고쳐서(기존 cursor_limit은 커서의 위치를 배열의 테두리에 제한하는 반면 변경된 함수는 커서의 위치에서 4*4영역을 탐색하여 판별하는 것으로 테두리영역 근처에서 1칸을 남기고 접근을 못하는 버그를 해결함.) 버그 수정 및 메뉴와 싱글 이어주는 작업 완료 1.0V 개발완료.
<br>
- 1.01 업데이트 예정 : single play UI 업데이트 예정(스코어, 콤보, 설명, next_block_ui,etc)

![captet](https://github.com/rudcks5562/Tetris/assets/72645618/8f59985f-dd96-4b80-9265-24a371f83fa8)
