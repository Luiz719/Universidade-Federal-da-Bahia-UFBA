package SistemaBiblioteca.src.components;

import SistemaBiblioteca.src.components.livros.Livro;
import SistemaBiblioteca.src.components.usuarios.Usuario;

public class VerificadorGrad implements VerificadorEmprestimo {

    public boolean autorizaEmprestimo(Usuario usuario, Livro livro) {
       
        if(!livro.podeSerEmprestado()) return false;
        if(!usuario.podeEmprestar()) return false;

        if(livro.temMaisReservasQueExemplares() && !usuario.livroEstaReservado(livro.getId())){
            Mensagem.emprestimoMalSucedidoPorReserva();
            return false;
        }

        if(usuario.exemplarEstaEmprestado(livro.getId())){ 
            Mensagem.livroJaEmprestado();
            return false;
        }
        return true;
    }
    
}
