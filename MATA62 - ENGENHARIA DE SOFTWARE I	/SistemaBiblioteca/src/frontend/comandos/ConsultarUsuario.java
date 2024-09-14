package SistemaBiblioteca.src.frontend.comandos;

import SistemaBiblioteca.src.components.Emprestimo;
import SistemaBiblioteca.src.components.Reserva;
import SistemaBiblioteca.src.components.livros.Livro;
import SistemaBiblioteca.src.components.usuarios.Usuario;
import SistemaBiblioteca.src.frontend.Biblioteca;

import java.time.LocalDateTime;

public class ConsultarUsuario implements Comando {

    @Override
    public Object executar(int ... params) throws IllegalArgumentException {
        if (params.length < 1) {
            throw new IllegalArgumentException("O comando deve receber o seguinte parâmetro: ID do usuário.");
        }

        Biblioteca biblioteca = Biblioteca.obterInstancia();
        Usuario usuario = biblioteca.consultarUsuario(params[0]);

        if (usuario == null) {
            System.out.println("Não existe usuário de ID = " + params[0]);
            return false;
        }

        System.out.println("Nome do Usuário: " + usuario.getNome());
        System.out.println("ID do Usuário: " + usuario.getID());

        System.out.println("\nEmpréstimos em curso:");

        for (int i = 0; i < usuario.getNumeroEmprestimos(); i++) {
            Emprestimo emprestimo = usuario.getEmprestimo(i);

            Livro livro = biblioteca.consultarLivro(emprestimo.getCodLivro());
            String titulo = livro.getTitulo();

            LocalDateTime dataEmprestimo = emprestimo.getDataEmprestimo();
            LocalDateTime dataDevolucao = emprestimo.getDataDevolucao();

            System.out.println("  - Livro \"" + titulo + "\"");
            System.out.println("    - Data do empréstimo: " + dataEmprestimo);
            System.out.println("    - Data para devolução: " + dataDevolucao);
        }

        System.out.println("\nEmpréstimos finalizados:");

        for (int i = 0; i < usuario.getNumeroEmprestimosFinalizados(); i++) {
            Emprestimo emprestimo = usuario.getEmprestimoFinalizado(i);

            Livro livro = biblioteca.consultarLivro(emprestimo.getCodLivro());
            String titulo = livro.getTitulo();

            LocalDateTime dataEmprestimo = emprestimo.getDataEmprestimo();
            LocalDateTime dataDevolucao = emprestimo.getDataFinalizado();

            System.out.println("  - Livro \"" + titulo + "\"");
            System.out.println("    - Data do empréstimo: " + dataEmprestimo);
            System.out.println("    - Data da devolução: " + dataDevolucao);
        }

        System.out.println("\nReservas:");

        for (int i = 0; i < usuario.getNumeroReservas(); i++) {
            Reserva reserva = usuario.getReserva(i);

            Livro livro = biblioteca.consultarLivro(reserva.getCodLivro());
            LocalDateTime data = reserva.getDataReserva();

            System.out.println("  - Livro \"" + livro.getTitulo() + "\" reservado no dia " + data);
        }
        return true;
    }
}

