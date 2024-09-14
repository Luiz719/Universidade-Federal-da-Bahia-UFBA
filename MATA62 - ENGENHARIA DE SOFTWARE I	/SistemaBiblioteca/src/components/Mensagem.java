package SistemaBiblioteca.src.components;

public class Mensagem {
    public static void emprestimoNaoEncontrado(){
        System.out.println("----------------");
        System.out.println("Sinto muito, mas não há empréstimo em aberto desse livro para esse usuário.");
        System.out.println("Por favor, tente novamente");
        System.out.println("----------------");
    }

    public static void emprestimoMalSucedidoPorReserva(){
        System.out.println("----------------");
        System.out.println("Sinto muito, a quantidade de reservas existentes do livro é maior ou igual à quantidade de exemplares disponíveis, e o usuário não tem reserva para ele.");
        System.out.println("Por favor, tente novamente");
        System.out.println("----------------");
    }

    public static void livroJaEmprestado(){
        System.out.println("----------------");
        System.out.println("Sinto muito, mas já há empréstimo em aberto desse livro para esse usuário.");
        System.out.println("Por favor, devolva seu exemplar antes de tentar um novo empréstimo.");
        System.out.println("----------------");
    }

    public static void usuarioDevedor(){
        System.out.println("----------------");
        System.out.println("Sinto muito, mas você tem um empréstimo em atraso.");
        System.out.println("Por favor, efetue a devolução antes de realizar um novo empréstimo.");
        System.out.println("----------------");
    }

    public static void noLimiteEmprestimo(){
        System.out.println("----------------");
        System.out.println("Sinto muito, mas você já atingiu o limite de empréstimos.");
        System.out.println("Por favor, efetue uma devolução antes de realizar um novo empréstimo.");
        System.out.println("----------------");
    }

    public static void noLimiteReserva(){
        System.out.println("----------------");
        System.out.println("Sinto muito, mas você já atingiu o limite de reservas.");
        System.out.println("Por favor, desfaça uma de suas reservas antes de realizar uma nova.");
        System.out.println("----------------");
    }

    public static void exemplarIndisponivel(){
        System.out.println("----------------");
        System.out.println("Sinto muito, mas não há disponibilidade de exemplar desse livro na biblioteca.");
        System.out.println("Por favor, tente novamente.");
        System.out.println("----------------");
    }
}
