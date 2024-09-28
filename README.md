
# 9irSH

Welcome to **9irSH**, a lightweight and user-friendly shell designed for Unix-like operating systems. This project is a mini shell that supports basic command execution, piping, redirection... etc.

## Features

- **Basic Command Execution**: Run standard shell commands.
- **Piping**: Connect multiple commands with the pipe operator (`|`).
- **Redirection**: Redirect input and output using `>`, '>>', '<' and `<<`.
- **Environment Variables**: Access and modify environment variables.

## Installation

To install 9irSH, clone the repository and build the project:

```bash
git clone https://github.com/imranboutadghart/9irSH
cd 9irSH
make
```

## Usage

To start the shell, simply run:

```
./minishell
```

You will be greeted with a prompt. Type your commands and hit Enter!

### Examples

- Run a command:
  ```
  ls -l
  ```

- Use piping:
  ```
  cat file.txt | grep "search_term"
  ```

- Redirect output to a file:
  ```
  echo "Hello, World!" > output.txt
  ```

- Background execution:
  ```
  sleep 10
  ```

## Contributing

We welcome contributions! If you have suggestions or improvements, please create a pull request or open an issue.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/YourFeature`)
3. Commit your changes (`git commit -m 'Add some feature'`)
4. Push to the branch (`git push origin feature/YourFeature`)
5. Open a pull request

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgments

big Thanks to my homie who prefers to stay anon, and the 1337 community for supporting this project. Special thanks to the various resources and tutorials that helped in the development of 9irSH.

## Contact

For questions or feedback, feel free to reach out:

- Email: imranboutadghart1@gmail.com
- GitHub: [imranBoutadghart](https://github.com/imranboutadghart)

Happy coding!