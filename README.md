# [C++] Mart System Project

## 개요

전반적인 마트 시스템을 이해하기 위한 프로젝트로, C++을 이용하여 Console 온라인 마켓 및 고객 구매 서비스를 구현

- 회원을 관리하는 **로그인 페이지**
- 마트의 물건 품목과 재고를 관리하는 **관리자 페이지**
- 해당 마트의 물품을 사는 **고객 페이지**

<br>

![martsystem](./image/martsystem.png)

<br>

## 사용한 기술 스택

- C++
- MySQL
- Visual Studio

<br>

## 기능설명

### Login Page

- **로그인 :** 회원가입을 바탕으로 관리자 및 고객으로 로그인하여 각 페이지로 이동하는 기능
    - 관리자는 여러 아이디로 하나의 관리자용 페이지 이용
    - 고객은 각 개인별 페이지 이용
- **회원가입 :** 아이디와 비밀번호, 역할(관리자/고객)을 선택하여 가입하는 기능
    - 고객으로 회원가입시, 한 계정당 장바구니 DB와 구매내역 DB 생성
- **회원 관리 :** 현재 가입된 회원(고객/관리자) 명단을 출력하는 기능

### Manager Page

- **품목 목록 :** 현재 존재하는 품목들을 목록형태로 나열하여 나타냄
- **품목 추가 :** 현재 품목에 존재하지 않는 품목을 추가하는 기능
- **품목 삭제 :** 현재 품목에 존재하는 품목을 삭제하는 기능
- **품목 수정 :** 존재하는 품목의 이름/가격/소비자 가격/속성 전체를 수정할 수 있는 기능
- **입고 :** 현재 존재하는 품목에 한하여 재고를 추가하는 기능
- **출고 :** 현재 존재하는 품목에 한하여 재고를 없애는 기능
- **누적 판매 수익 :** 고객들이 구매한 가격을 합산하여 해당 마트의 누적 판매 수익을 보여주는 기능

### Customer Page

- **장바구니 목록 :** 고객이 장바구니에 추가한 항목을 보여주는 기능
- **장바구니 추가 :** 관리자가 관리하는 품목 중 구매할 품목을 장바구니에 추가하는 기능
- **장바구니 삭제 :** 한 품목에 대하여 삭제하거나 장바구니 전체 품목을 삭제하는 기능
- **카트 물품 변경 :** 장바구니 안에 있는 개별 품목의 수량을 추가/삭제하는 기능
- **구매 :** 장바구니에 있는 물품을 구매하는 기능
- **환불 :** 자신이 구매했던 물품을 환불하는 기능
- **주문 내역 :** 자신이 구매 혹은 환불한 내역을 확인할 수 있는 기능

<br>

## 담당 역할 및 성과

**담당역할**

- 개인프로젝트로 모든 기능을 개발
- 로그인 페이지, 관리자 페이지, 고객 페이지, MySQL 등

**성과**

이 프로젝트를 통해 마트의 일부분이 아닌, 전반적인 시스템의 흐름을 알 수 있었으며 특히나 Database(MySQL)의 CRUD와 관련된 기능을 확실히 구현할 수 있게됨

<br>

## 개발 기간

- 2021.09.07~2021.11.7(약 2달)
- 이후 일부 시스템 수정

<br>

## Reference

[[C++] Mart System (초기)기획서](https://www.notion.so/C-Mart-System-e4bb1a9a0cd046d7bd4734c44eaaec13)

[DB 명세서](https://www.notion.so/DB-a9b356f970234b97b811c29582447b7e)
