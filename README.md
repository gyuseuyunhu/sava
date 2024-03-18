# webserv

## Team
<table align="center">
  <th>gyuhong</th>
  <th>seulee2</th>
  <th>yunjcho</th>
  <th>hujeong</th>
  <tr>
    <td><img src="https://avatars.githubusercontent.com/u/108771739?v=4" width="140" height="140"/></td>
    <td><img src="https://avatars.githubusercontent.com/u/96572410?v=4" width="140" height="140"/></td>
    <td><img src="https://avatars.githubusercontent.com/u/73283078?v=4" width="140" height="140"/></td>
    <td><img src="https://avatars.githubusercontent.com/u/114281631?v=4" width="140" height="140"/></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/guune">홍규선</a>
    </td>
    <td align="center"><a href="https://github.com/sngsho">이승효</a>
    </td>
    <td align="center"><a href="https://github.com/YunjooCho">조윤주</a>
    </td>
    <td align="center"><a href="https://github.com/heehoh">정희호</a>
    </td>
  </tr>
</table>

## About
HTTP/1.1 프로토콜 기반으로 소켓 통신을 하는 웹서버를 C++로 구현하는 프로젝트 입니다.  
웹서버를 가상호스팅, 라우팅 등을 설정 파일을 통해 동작시킬 수 있습니다.  
I/O Multiplexing 함수인 kqueue()를 사용해서 들어오는 요청을 비동기적으로 처리합니다.  

## Overview


https://github.com/gyuseuyunhu/server/assets/114281631/0d8aa302-ed84-41e0-aab0-7b540dbfd2b9



## Usage
이 프로젝트는 mac os 환경에서 동작합니다.
```
make
export WEBSERV_ROOT=$PWD
./webserv [Config File]
```

## Flow
<img width="1052" alt="flow" src="https://github.com/gyuseuyunhu/server/assets/114281631/50c9bbc0-903e-4e12-a969-29f1a98b8d3d">

- 설정 파일을 파싱해서 port, host, location 등 설정 대로 웹서브를 동작시킵니다.
- 클라이언트가 연결을 요청하면 요청을 수락하고 연결을 맺습니다.
- 요청을 맺은 후 클라이언트의 메세지를 해석하고 클라이언트의 요청 url이 일반 파일인지 CGI인지 확인합니다.
- 일반 파일에 대한 요청이면 파일을 읽은 후 응답 메세지에 담아 클라이언트에게 전송합니다.
- CGI 요청이면 CGI 프로세스를 동작시킨 후 CGI 프로세스와 통신하여 응답 메세지를 생성하고 클라이언트에게 전송합니다.
- 클라이언트에게 응답 메세지를 전송한 뒤 다시 클라이언트의 요청 메세지를 기다립니다(keep-alive).

## Detail
### 설정 파일
#### 가상 호스팅
- 하나의 웹서버에서 여러 도메인 이름을 호스팅하는 방법입니다.
- 크게 이름 기반(name-based), IP 기반(IP-based) 가상 호스팅으로 나뉩니다.
- 이름 기반 가상 호스팅에서는 동일한 IP 주소에 대해 여러 호스트 이름을 사용할 수 있고, 클라이언트는 요청메세지에 Host 헤더를 명시해야 합니다.
- IP 기반 가상 호스팅은 각 웹사이트마다 다른 IP 주소 또는 Port를 가지는 방식입니다.
- 이 프로젝트는 이름 기반 가상 호스팅을 지원하며, nginx랑 유사하게 서버블록 내의 server_name을 다르게 함으로써 작동합니다.

#### HTTP 메세지
- HTTP 메세지는 요청 메세지와 응답 메세지 두 종류로 분류할 수 있습니다.
```
// 요청 메세지
GET / HTTP/1.1
Host: localhost

// 응답 메세지
HTTP/1.1 200 OK
Content-type: text/html; charset=UTF-8
Content-length: 2134

(바디 생략)
```
- HTTP 메세지는 시작줄 헤더 본문으로 나누어 해석합니다.
- HTTP 요청 메세지의 시작줄은 메소드, 경로, 프로토콜로 구성되어 있습니다.
- 이 프로젝트는 GET, POST, DELETE 메소드를 지원하며, HTTP/1.1에 따라 응답을 보낸 뒤에도 소켓 연결을 지속합니다.
- 헤더의 Host와 시작줄의 경로를 확인하고, 요청에 따른 응답 메세지를 시작줄 헤더 본문으로 구성해서 소켓을 통해 전송합니다.
- Host 헤더는 필수 필드로 요청 메세지 Host 헤더가 없을 시 400 Bad Request를 응답합니다.
- Content-length로 전달된 길이만큼 본문을 읽습니다.
- 응답도 시작줄, 헤더, 본문으로 구성되어 있습니다.
- 시작줄의 상태코드로 요청이 성공적으로 완료되었는지 확인할 수 있고, 이 프로젝트는 200번대부터 500번대까지 다양한 상태코드를 지원합니다.

## 참고자료
- [가상 호스팅](https://en.wikipedia.org/wiki/Virtual_hosting)
- [HTTP 메세지](https://developer.mozilla.org/ko/docs/Web/HTTP/Messages)

