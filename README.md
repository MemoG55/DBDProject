# DBDProject

## 팀원
+ 정민수(팀장): 생존자
+ 모명준: 오브젝트 / 게임플로우
+ 김미진: 살인마
+ 유호근: 맵 / 정보 시스템


## 제작 기간
09.01.2025 - 11.07.2025


## Stacks
### Development
<div>
<img src="https://img.shields.io/badge/C++-512BD4?style=flat-square&logo=c++&logoColor=white"/>
<img src="https://img.shields.io/badge/Unreal-000000?style=flat-square&logo=unreal&logoColor=white"/>
</div>

### Tools & Communication
<div>
<img src="https://img.shields.io/badge/Notion-000000?style=flat-square&logo=notion&logoColor=white"/>
<img src="https://img.shields.io/badge/Discord-5865F2?style=flat-square&logo=discord&logoColor=white"/>
</div>

### Version Control
<div>
<img src="https://img.shields.io/badge/Perforce-4C00FF?style=flat-square&logo=perforce&logoColor=white"/>
</div>

## 자료
[프로젝트 계획 PPT](https://drive.google.com/drive/u/0/folders/17ca7VNNtwfffXQOK5RL3rLxDTOYegnmb)

## 참고
+ 해당 언리얼 파일은 Asset이 빠진 버전으로 정상 구동이 되지 않습니다
+ 깃허브는 언리얼 파일의 Source Code 확인용으로만 사용하시고, 구동은 실행 영상과 PPT를 참고해주시길 바랍니다


sequenceDiagram
    participant C as AController
    participant S as ASurvivorCharacter
    participant I as ASurvivorItem
    participant A as UAddonComponent
    participant D as DataTable
    participant Att as USurvivorAttributeSet

    C->>S: PossessedBy(NewController)  호출
    activate S
    S->>S: ServerSideInit() 호출
    note right of S: 로드아웃 확인
    alt 아이템 설정됨 (InitialItemInfo 존재)
        S->>S: InitializeEquippedItem(InitialItemInfo)  호출

        note right of S: 아이템 스폰 및 초기화
        S->>D: 아이템 클래스 조회 (InitialItemInfo)
        D-->>S: 아이템 클래스 반환
        S->>I: 스폰(Spawn Item Class)
        activate I

        note right of S: 애드온 1,2 초기화
        S->>D: 애드온 클래스 조회
        D-->>S: 애드온 클래스 반환
        S->>A: 스폰 & Attach (애드온은 컴포넌트)
        activate A
        A->>A: OnInitialized() 호출
        deactivate A

        S->>S: EquipItem(스폰한 아이템)
        note right of S: 아이템을 캐릭터에 부착
        S->>I: AttachToCharacter
        I->>I: OnEquipItem()

        note right of I: 아이템 장착
        I->>Att: 아이템 내구도 어트리뷰트 초기화
        I->>A: OnEquip() 호출
        I->>I: 아이템 어빌리티 부여
        I->>I: OnInitialized()  호출

        deactivate I
    else 아이템 설정 안됨
        S-->>S: 초기화 스킵
    end
    deactivate S
