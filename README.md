# Philosophers

## 42seoul subject

- 본 과제는 42seoul 과정의 과제입니다.
- 제한된 라이브러리를 사용하여 요구하는 조건을 충족시키는 프로그램을 구현하는 과정에서 cs지식을 학습할 수 있습니다.
- 이 과제를 통해 mutex를 이용하여 multi thread 에서 발생하는 동시성 문제에 대해 학습하였습니다.
- 원형 테이블에서 철학자의 식사 시뮬레이션을 통해 동시성 문제를 해결하는 42seoul 과제입니다.
## Usage

```
$ cd philo
$ make
$ ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```
## 파라미터 설명
#####  `number_of_philosophers`
- 시뮬레이션에 사용되는 철학자와 포크의 수
- 철학자들은 원형 식탁에 앉아 있고, 포크는 철학자와 철학자 사이에 위치해있습니다.
- 식사를 위해서는 철학자가 본인의 좌측과 우측에 있는 포크를 모두 점유해야합니다.
##### `time_to_die`
- 다음 식사까지 생존가능한 시간 ms
- 철학자가 식사를 시작한 뒤부터 다음 식사를 하지 않은 채 이 시간이 지나면 철학자는 굶어 죽게됩니다.

##### `time_to_eat`
- 철학자 식사에 걸리는 시간 ms

##### `time_to_sleep`
- 철학자 수면에 소요되는 시간 ms
- 철학자는 식사가 끝나면 즉시 수면을 취합니다.

##### `number_of_times_each_philosopher_must_eat` (옵션)
- 철학자들의 식사 횟수
- 모든 철학자들이 각자 이 횟수 만큼 식사를 마치면 시뮬레이션 중지합니다.
- 옵션을 사용하지 않는 경우에는 한 철학자라도 사망하면 중지합니다.

##  입력 값 제한 사항

- number_of_philosophers < 200
- time_to_die > 60
- time_to_eat > 60
- time_to_sleep > 60

## 출력 양식
- 철학자가 포크를 잡음, 식사, 취침, 사망시 출력
- [현재 시간 ms] [철학자 번호] [상태]

## 동시성 문제 해결 방법
- 공유자원인 포크를 점유하기 전에 각 포크의 mutex를 lock
- 식사가 끝나면 각 포크의 mutex를 unlock
- 출력하기 이전에 출력 mutex를 lock
- 출력이 끝난 뒤 출력 mutex를 unlock
## 예시

```
./philo 1 800 200 200

철학자가 한명, 포크도 1개 이기 때문에 식사를 하지 못해 800ms 뒤 사망
```
![](https://velog.velcdn.com/images/i-no/post/c10319d6-a0a2-40c0-8315-c5f65ebd822f/image.png)


```
./philo 5 800 200 200

철학자 식사 사이의 간격이 400ms로 800ms보다 낮아 무한히 식사
```
![](https://velog.velcdn.com/images/i-no/post/adac3c92-00ce-42ff-8339-cee93050b467/image.png)

```
./philo 5 800 200 200 7

종료 조건에 맞게 모든 철학자들이 7번 이상 식사 이후 종료
```
![](https://velog.velcdn.com/images/i-no/post/95a81b56-805f-4563-9878-f49a3737646d/image.png)

```
./philo  4 310 200 100 

철학자 식사 시간이 200ms로 철학자 식사 이후 다른 철학자가 식사하는 200ms가 지나면 400ms로 310ms를 초과하여 사망
```

![](https://velog.velcdn.com/images/i-no/post/cc7d654f-cb10-491f-a9bd-91b0f6f837b6/image.png)

