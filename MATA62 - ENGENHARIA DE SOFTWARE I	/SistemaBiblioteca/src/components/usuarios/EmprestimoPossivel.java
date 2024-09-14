package SistemaBiblioteca.src.components.usuarios;

public class EmprestimoPossivel implements EstadoUsuarioEmprestimo {

    @Override
    public boolean podeEmprestar(Usuario usuario) {

        return true;
    }

}
