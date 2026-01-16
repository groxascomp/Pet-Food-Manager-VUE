<template>
  <nav class="w-full bg-gray-800">
    <div class="px-4 sm:px-6 lg:px-8">
      <div class="flex h-16 items-center justify-between">
        
        <span class="text-white font-bold text-lg">PetF.</span>

       
        <div class="flex items-center sm:hidden">
          <button
            type="button"
            @click="mobileOpen = !mobileOpen"
            class="p-2 rounded-md text-gray-400 hover:bg-gray-700 hover:text-white"
          >
            <span class="sr-only">Open main menu</span>
            <svg
              v-if="mobileOpen"
              class="h-6 w-6"
              fill="none"
              stroke="currentColor"
              stroke-width="1.5"
              viewBox="0 0 24 24"
            >
              <path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" />
            </svg>
            <svg
              v-else
              class="h-6 w-6"
              fill="none"
              stroke="currentColor"
              stroke-width="1.5"
              viewBox="0 0 24 24"
            >
              <path stroke-linecap="round" stroke-linejoin="round" d="M3.75 6.75h16.5M3.75 12h16.5m-16.5 5.25h16.5" />
            </svg>
          </button>
        </div>
      </div>
    </div>

    
    <div v-if="mobileOpen" class="sm:hidden px-2 pt-2 pb-3 space-y-1">
     
    </div>
  </nav>
</template>

<script setup>
import { ref } from 'vue'

const mobileOpen = ref(false)
</script>

<style scoped>

</style>
