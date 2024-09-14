package SistemaBiblioteca.src.frontend;

import java.util.Scanner;


public class UserInput {
    private String command;
    private int[] args;
    private Scanner scanner;

    public UserInput() {
        this.scanner = new Scanner(System.in);
    }

    private void parseInputData(String inputLine) throws IllegalArgumentException {
        String[] data = inputLine.split(" ");
        String errorMessage;

        if (data.length < 1) {
            errorMessage = "Formato de entrada inválido: informe o comando e os seus argumentos.";
            throw new IllegalArgumentException(errorMessage);
        }

        int[] args = new int[data.length - 1];

        this.command = data[0];

        try {
            for (int i = 0; i < data.length - 1; i++) {
                args[i] = Integer.parseInt(data[i + 1]);
            }
        } catch (Exception error) {
            errorMessage = "Formato de entrada inválido: Os argumentos devem ser inteiros positivos.";
            throw new IllegalArgumentException(errorMessage);
        }
        this.args = args;
    }

    public void close() {
        this.scanner.close();
    }

    public int[] getArgs() {
        return this.args;
    }

    public String getCommand() {
        return this.command;
    }

    public void read() throws IllegalArgumentException {
        String inputLine = this.scanner.nextLine();
        this.parseInputData(inputLine);
    }
}
