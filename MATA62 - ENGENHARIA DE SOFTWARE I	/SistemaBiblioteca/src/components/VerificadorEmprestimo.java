package SistemaBiblioteca.src.components;

import SistemaBiblioteca.src.components.livros.Livro;
import SistemaBiblioteca.src.components.usuarios.Usuario;

public interface VerificadorEmprestimo {

    public boolean autorizaEmprestimo(Usuario usuario, Livro livro);

}
