# docker 学习

地址： https://yeasy.gitbook.io/docker_practice/

### 镜像

#### 使用镜像

可以使用这条指令

```sh
docker run -it --rm ubuntu:18.04 bash
```

`-i`表示，交互式

`-t`表示，终端

`--rm`表示，容器结束以后，直接删除

可以使用`cat /etc/os-release`来查看系统的版本

#### 端口映射、按照命名、守护进程

```sh
docker run --name webserver -d -p 80:80 nginx
```

#### dockrfile

尽量少的使用`RUN`，`RUN`相当于是每次叠加了一层（不理解没关系），反正知道大概是这么用就行

正确写法如下：

```dockerfile
FROM debian:stretch

RUN set -x; buildDeps='gcc libc6-dev make wget' \
    && apt-get update \
    && apt-get install -y $buildDeps \
    && wget -O redis.tar.gz "http://download.redis.io/releases/redis-5.0.3.tar.gz" \
    && mkdir -p /usr/src/redis \
    && tar -xzf redis.tar.gz -C /usr/src/redis --strip-components=1 \
    && make -C /usr/src/redis \
    && make -C /usr/src/redis install \
    && rm -rf /var/lib/apt/lists/* \
    && rm redis.tar.gz \
    && rm -r /usr/src/redis \
    && apt-get purge -y --auto-remove $buildDeps
    # 最后一行表示清理
```

最后`docker build -t nginx:v3 .`，这里`-t nginx:v3`，这就会得到我自己的镜像，可以在`docker image ls`中看到

#### 上下文路径

上面的`docker build -t nginx:v3 .`，这个`.`就是上下文。
我们在这 dockerfile 中，不能使用`../`或者是`/opt/*`这样的路径，因为超过了上下文的范围。

#### 程序应该以前台运行，而不是守护进程

####
