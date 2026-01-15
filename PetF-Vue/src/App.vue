<template>
  <div id="app">
    <!-- Show TopBar + NavBar everywhere except login routes -->
    <TopBar v-if="!isLoginRoute" />
    <NavBar v-if="!isLoginRoute" />

    <!-- Render active page -->
    <RouterView />

    <Footer v-if="!isLoginRoute" />
  </div>
</template>

<script setup>
import { computed } from 'vue'
import { useRoute } from 'vue-router'

// Components
import TopBar from './components/TopBar.vue'
import NavBar from './components/NavBar.vue'
import Footer from './components/Footer.vue'

const route = useRoute()

// Hide TopBar/NavBar/Footer on login and login-anim routes
const isLoginRoute = computed(() =>
  route.path === '/login' || route.path === '/login-anim'
)
</script>

<style>
@import './App.css';
</style>
