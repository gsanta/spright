Rails.application.routes.draw do
  root "editor#index"
  get "/editor", to: "editor#index"

  resources :drawings, only: %i[index show create update destroy]

  devise_for :users, controllers: {
    sessions: 'users/sessions',
    registrations: 'users/registrations',
  }

  # For details on the DSL available within this file, see https://guides.rubyonrails.org/routing.html
end
