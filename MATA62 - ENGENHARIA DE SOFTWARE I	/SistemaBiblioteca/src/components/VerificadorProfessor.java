package SistemaBiblioteca.src.components;

import SistemaBiblioteca.src.components.livros.Livro;
import SistemaBiblioteca.src.components.usuarios.Usuario;

public class VerificadorProfessor implements VerificadorEmprestimo {

    @Override
    public boolean autorizaEmprestimo(Usuario usuario, Livro livro) {

        if(!livro.podeSerEmprestado()) return false;
        if(!usuario.podeEmprestar()) return false;

        return true;
    }

}
