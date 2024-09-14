package SistemaBiblioteca.src;

import SistemaBiblioteca.src.frontend.UserInput;
import SistemaBiblioteca.src.frontend.comandos.ComandoExecutor;

public class Programa {
    public static void main(String[] args) throws Exception {
        ComandoExecutor comandoExecutor = new ComandoExecutor();
        UserInput userInput = new UserInput();

        InitFabrica.initTeste();

        System.out.println("Comando disponíveis:");
        System.out.println("- Consultar Notificações: ntf <user_id>");
        System.out.println("- Consultar Livro: liv <book_id>");
        System.out.println("- Consultar Usuário: usu <user_id>");
        System.out.println("- Devolver Livro: dev <user_id> <book_id>");
        System.out.println("- Realizar Empréstimo: emp <user_id> <book_id>");
        System.out.println("- Registrar Observador: obs <user_id> <book_id>");
        System.out.println("- Reservar Livro: res <user_id> <book_id>");
        System.out.println("- Sair do Sistema: sai");
        
        while(true) {
            System.out.print("\nInforme o comando e os seus argumentos: ");

            try {
                userInput.read();

                String command = userInput.getCommand();
                int[] arguments = userInput.getArgs();
                
                comandoExecutor.executarComando(command, arguments);

            } catch (IllegalArgumentException error) {
                System.out.println(error.getMessage());

            } catch (InterruptedException error) {
                System.out.println(error.getMessage());
                userInput.close();
                break;
            }
        }
    }
}
