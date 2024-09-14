package SistemaBiblioteca.src.frontend.comandos;

import SistemaBiblioteca.src.components.Emprestimo;
import SistemaBiblioteca.src.components.Reserva;
import SistemaBiblioteca.src.components.livros.Livro;
import SistemaBiblioteca.src.components.livros.LivroExemplar;
import SistemaBiblioteca.src.components.livros.StatusExemplar;
import SistemaBiblioteca.src.components.usuarios.Usuario;
import SistemaBiblioteca.src.frontend.Biblioteca;

public class ConsultarLivro implements Comando {

    @Override
    public Object executar(int ... params) throws IllegalArgumentException {
        if (params.length < 1) {
            throw new IllegalArgumentException("O comando deve receber o seguinte parâmetro: ID do livro.");
        }

        Biblioteca biblioteca = Biblioteca.obterInstancia();

        Livro livro = biblioteca.consultarLivro(params[0]);

        if (livro == null) {
            System.out.println("Não existe livro de ID = " + params[0]);
            return false;
        }

        int reservas = livro.getNumeroReservas();
        int exemplares = livro.getNumeroExemplares();

        System.out.println("Título do Livro: " + livro.getTitulo());
        System.out.println("ID do Livro: " + livro.getId());
        System.out.println("Número de Exemplares: " + exemplares);
        System.out.println("Número de Reservas: " + reservas);

        if (reservas > 0) {
            System.out.println("\n Reservas:");
        }

        for (int index = 0; index < reservas; index++) {
            Reserva reserva = livro.getReserva(index);
            Usuario usuario = biblioteca.consultarUsuario(reserva.getCodUsuario());
            System.out.println("  - " + usuario.getNome());
        }

        if (exemplares > 0) {
            System.out.println("\n Exemplares:");
        }

        for (int index = 0; index < exemplares; index++) {
            LivroExemplar exemplar = livro.getExemplar(index);

            if (exemplar.getStatus() == StatusExemplar.Emprestado) {
                Emprestimo emprestimo = exemplar.getEmprestimo();
                Usuario usuario = emprestimo.getSolicitante();
                
                System.out.println("  - Exemplar " + exemplar.getCodExemplar() + " foi emprestado para " + usuario.getNome());
                System.out.println("    - Data do empréstimo: " + emprestimo.getDataEmprestimo());
                System.out.println("    - Data de devolução: " + emprestimo.getDataDevolucao());
            }
            else {
                System.out.println("  - Exemplar " + exemplar.getCodExemplar() + " está disponível");
            }
        }
        return true;
    }
}
