cmake_minimum_required(VERSION 3.19)
project(lojacalcados LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql)

qt_standard_project_setup()

qt_add_executable(lojacalcados
    WIN32 MACOSX_BUNDLE

    principal.cpp
    principal.h
    principal.ui
    cadastroprodutos.h cadastroprodutos.cpp cadastroprodutos.ui
    cadastrovendedor.h cadastrovendedor.cpp cadastrovendedor.ui
    cadastro_cliente.h cadastro_cliente.cpp cadastro_cliente.ui
    inserir_produtos.h inserir_produtos.cpp inserir_produtos.ui
    remover_produtos.h remover_produtos.cpp remover_produtos.ui
    controle_vendedores.h controle_vendedores.cpp controle_vendedores.ui
    controle_vendas.h controle_vendas.cpp controle_vendas.ui
    controle_estoque.h controle_estoque.cpp controle_estoque.ui
    resources.qrc

    vendedor.h vendedor.cpp


    banco_de_dados.h banco_de_dados.cpp
    main.cpp
)

target_link_libraries(lojacalcados
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
)

include(GNUInstallDirs)

install(TARGETS lojacalcados
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET lojacalcados
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
