# QMK Docker Bootstrapper

This is a project designed to allow segregation between QMK's core logic and keyboard layouts.

## Advantages

* Small, easily-digestible repository makes getting started quick and easy
* No complex prerequisite installations
* Easy to keep QMK core up-to-date without maintaining a separate fork of the whole QMK repo
* Clean local machine - if QMK ever changes its prerequites, no need to worry about removing obsolete or obscure packages

## Prerequisites

[Docker](https://www.docker.com/get-started)

That's it. You don't need to run a fancy install script or install a bunch of seemingly-random packages.

**Note on Windows:** Docker for Windows is a mature and stable tool that works just like Docker on any other OS. However, this version requires Windows 10. If you're still on an older version of Windows, you can use "Docker Toolbox," a slightly clunkier version of Docker. It's still totally usable, but it's a bit more fiddly to get set up.

## Usage

### Initial setup

1. Clone this repository
1. Open `docker-compose.yml` and check the following:
    1. Under the `environment` section, update the `keyboard` and `layout` properties to match your keyboard and layout, respectively.
    1. Under the `volumes` section, set up a volume for your keyboard.

The example keymap provided with this repo is the "default" firmware for the Ergodox EZ.

### Compiling QMK

Run a single command to build the Docker container with the QMK firmware:

`docker-compose build --skip-cache`

Typically, this only needs to be run once, but you can re-run it at any time to update to the latest version of QMK.

### Compiling

Develop in your keymap.c file as normal.

When you're ready to compile, open a command prompt and browse to your working directory. Then, run this command:

`docker-compose up`

Your .hex file will be copied to the `/output` directory in the working directory.

Repeat this command any time you need to rebuild your keyboard firmware.

## Advanced Usage

### Multiple keyboards

You can build multiple keyboards at the same time by setting the `keyboard` variable in `docker-compose.yml` to a comma-separated list. Then, add an additional volume for each keyboard to build.

For example, here's a snippet from a file that will build both an Ergodox and an Atreus layout:

```yaml
qmk:
    environment:
        keyboard: 'ergodox_ez,atreus'
        layout: 'default'
    volumes:
        # Ergodox directory
        - type: bind
          source: ./ergodox
          target: /qmk_firmware/keyboards/ergodox_ez/keymaps/username

        # Atreus directory
        - type: bind
          source: ./atreus
          target: /qmk_firmware/keyboards/atreus/keymaps/username
```

You can also use a comma-separated list in the `layout` variable.

If you use a comma-separated list in both variables, the process will build every combination of keyboard and layout.

### Building in parallel

Instead of building each keyboard layout in sequence, you can also duplicate the `qmk` service and set each one to a different layout to build them in parallel instead of in series. This results in a longer, messier `docker-compose.yml` file, but a faster build.

### User space directory

QMK allows generalization of code into a "user space" directory in the /users/\<username> directory. This can be accomplished in this system by adding an additional bind mount in the `volumes` key:

```yaml
qmk:
    volumes:
        # QMK user directory
        - type: bind
          source: ./user
          target: /qmk_firmware/users/username
```

Replace the "username" at the end of the target key with your username. This should typically match the name of the layout that will reference it.

## Contributing

I'm neither a QMK expert nor a Docker expert, so I'd be happy to accept contributions or feedback. My time is pretty limited, so don't be surprised if it takes me a while to respond, but I'd be happy to help as I'm able.
